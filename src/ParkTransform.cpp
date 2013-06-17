//!
//! @file 		ParkTransform.c
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		09/10/2012
//! @brief 		Contains the forward and inverse Park transformations, used in BLDC motor control.
//! @details
//!		<b>Last Modified:			</b> 29/10/2012					\n
//!		<b>Version:					</b> v1.0.0						\n
//!		<b>Company:					</b> CladLabs					\n
//!		<b>Project:					</b> Free code examples			\n
//!		<b>Language:				</b> C++						\n
//!		<b>Compiler:				</b> GCC						\n
//! 	<b>uC Model:				</b> PSoC5						\n
//!		<b>Computer Architecture:	</b> ARM						\n
//! 	<b>Operating System:		</b> FreeRTOS v7.2.0			\n
//!		<b>Documentation Format:	</b> Doxygen					\n
//!		<b>License:					</b> GPLv3						\n
//!		
//! 	Choice of either fixed-point (fast, but requires ) or double (slow) data types

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

#ifdef __cplusplus
extern "C" {
#endif

// PSoC
#include <device.h>

// GCC
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#ifdef __cplusplus
}
#endif

// User
#include "PublicDefinesAndTypeDefs.h"
#include "Config.h"
#include "./FixedPoint/FP.h"
#include "Bldc.h"
#include "Foc.h"
#include "UartDebug.h"
#include "ParkTransform.h"

//===============================================================================================//
//================================== PRECOMPILER CHECKS =========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#ifndef configPRINT_DEBUG_PARK_TRANSFORM
	#error Please define the switch configPRINT_DEBUG_PARK_TRANSFORM
#endif

#ifndef CDP
	#error Please define CDP. This is the bit place-value of the decimal point in a 32-bit fixed-point number. E.g. #define CDP 8 will give 8 bits of precision post DP, and 24 bits pre DP.
#endif

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace ParkTransform
{

	using namespace FixedP;

	//===============================================================================================//
	//=================================== PRIVATE TYPEDEF's =========================================//
	//===============================================================================================//

	// none

	//===============================================================================================//
	//==================================== PRIVATE VARIABLES ========================================//
	//===============================================================================================//

	#if(configPRINT_DEBUG_PARK_TRANSFORM == 1)
		//! Debug buffer
		static char _debugBuff[100] = {0};
	#endif

	fp<CDP> _sinLut[configPARK_LUT_SIZE] = {(int32_t)0};
	fp<CDP> _cosLut[configPARK_LUT_SIZE] = {(int32_t)0};

	//===============================================================================================//
	//====================================  FUNCTION PROTOTYPES =====================================//
	//===============================================================================================//

	//! @brief		Initialisation routines. Populates sin and cos LUT's.
	//!				Call before calling any other functions in ParkTransform.
	//! @note		Not thread-safe. Call from one task only.
	//! @public		
	void Init()
	{
		uint16_t i;
		
		#if(configPRINT_DEBUG_PARK_TRANSFORM == 1)
			UartDebug::PutString("PARK: Start of sin LUT values:\r\n");
		#endif

		for(i = 0; i < configPARK_LUT_SIZE; i++)
		{
			_sinLut[i] = fp<CDP>(sin(((double)i/(double)configPARK_LUT_SIZE)*2.0*PI));
			#if(configPRINT_DEBUG_PARK_TRANSFORM == 1)
				snprintf(_debugBuff, sizeof(_debugBuff), " %f,", Fix2Float<CDP>(_sinLut[i].intValue));
				UartDebug::PutString(_debugBuff);
			#endif
		}
		
		#if(configPRINT_DEBUG_PARK_TRANSFORM == 1)
			UartDebug::PutString("\r\nPARK: End of sin LUT values.\r\n");
		#endif
		
		#if(configPRINT_DEBUG_PARK_TRANSFORM == 1)
			UartDebug::PutString("PARK: Start of cos LUT values:\r\n");
		#endif

		for(i = 0; i < configPARK_LUT_SIZE; i++)
		{
			_cosLut[i] = fp<CDP>(cos(((double)i/(double)configPARK_LUT_SIZE)*2.0*PI));
			#if(configPRINT_DEBUG_PARK_TRANSFORM == 1)
				snprintf(_debugBuff, sizeof(_debugBuff), " %f,", Fix2Float<CDP>(_cosLut[i].intValue));
				UartDebug::PutString(_debugBuff);
			#endif
		}
		
		#if(configPRINT_DEBUG_PARK_TRANSFORM == 1)
			UartDebug::PutString("\r\nPARK: End of cos LUT values.\r\n");
		#endif
	}

	//! @brief 		Converts from stationary alpha-beta to rotating d-q reference frame.
	//! @details 	Uses fixed-point numbers and sin/cos LUT's. Call ParkTransform::Init() before
	//!				calling this function.							\n
	//! 			Maths:											\n
	//!						d = alpha*cos(theta) + beta*sin(theta)	\n
	//! 					q = beta*cos(theta) - alpha*sin(theta)	\n
	//!	@note		Execution Time: 192 clock cycles (4us @ 48MHz) (including function call)
	//! @note		Thread-safe.
	//! @public
	void Forward(fp<CDP> alpha, fp<CDP> beta, fp<CDP> theta, 
		fp<CDP> *d, fp<CDP> *q)
	{
		// Angle rounded to nearest degree
		//! @todo Fix this loss in precision
		*d = (alpha*_cosLut[theta.intValue>>CDP]) + (beta*_sinLut[theta.intValue>>CDP]);
		
		#if(configPRINT_DEBUG_PARK_TRANSFORM == 1)
			snprintf(_debugBuff, sizeof(_debugBuff), "PARK: sin(theta) = %f, cos(theta) = %f\r\n",  
				Fix2Float<CDP>(_sinLut[theta.intValue>>CDP].intValue), Fix2Float<CDP>(_cosLut[theta.intValue>>CDP].intValue));
			UartDebug::PutString(_debugBuff);
		#endif
		
		*q = (beta*_cosLut[theta.intValue>>CDP]) - (alpha*_sinLut[theta.intValue>>CDP]);
	}

	//! @brief 		Converts from stationary alpha-beta to rotating d-q reference frame
	//! @warning	Slow! Uses doubles and sin function
	//! @note		Thread-safe.
	//! @public
	void Forward(double alpha, double beta, double theta, double *d, double *q)
	{
		// d = alpha*cos(theta) + beta*sin(theta)
		// q = beta*cos(theta) - alpha*sin(theta)
		*d = alpha*cos(theta) + beta*sin(theta);
		*q = beta*cos(theta) - alpha*sin(theta);
	}

	//! @brief 		Converts from rotating d-q reference frame to stationary alpha-beta
	//! @details	Uses fixed-point mathematics. 
	//!				Call ParkTransform::Init() before calling this function.	\n
	//!					Maths:									\n
	//!					alpha = d*cos(theta) - q*sin(theta)		\n
	//! 				beta  = q*cos(theta) + d*sin(theta)		\n
	//! @note		Execution Time: 144 clock cycles (3us @ 48MHz) (including function call)
	//! @note		Thread-safe
	//! @public
	void Inverse(fp<CDP> d, fp<CDP> q, fp<CDP> theta, 
		fp<CDP> *alpha, fp<CDP> *beta)
	{
		
		*alpha= d*_cosLut[theta.intValue>>CDP] - q*_sinLut[theta.intValue>>CDP]; 
		*beta = q*_cosLut[theta.intValue>>CDP] + d*_sinLut[theta.intValue>>CDP];
	}

	//! @brief 		Converts from rotating d-q reference frame to stationary alpha-beta
	//! @details	
	//! @warning	Slow! Uses doubles and sin function
	//! @public
	void Inverse(double d, double q, double theta, double *alpha, double *beta)
	{
		// alpha = d*cos(theta) - q*sin(theta)
		// beta  = q*cos(theta) + d*sin(theta)
		*alpha= d*cos(theta) - q*sin(theta); 
		*beta = q*cos(theta) + d*sin(theta);
	}

} // namespace ParkTransform

// EOF