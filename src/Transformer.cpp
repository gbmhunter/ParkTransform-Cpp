//!
//! @file 			Transformer.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 		n/a
//! @created		2012/10/09
//! @last-modified 	2014/01/21
//! @brief 			Contains the forward and inverse Park transformations, used in BLDC motor control.
//! @details
//!					See the README in the repo root dir for more info.

//===============================================================================================//
//================================== PRECOMPILER CHECKS =========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//	

// GCC
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


// User headers
#include "../include/Config.hpp"
#include "../include/Transformer.hpp"



#ifndef config_PRINT_DEBUG_PARK_TRANSFORM
	#error Please define the switch config_PRINT_DEBUG_PARK_TRANSFORM
#endif

#ifndef CDP
	#error Please define CDP. This is the bit place-value of the decimal point in a 32-bit fixed-point number. E.g. #define CDP 8 will give 8 bits of precision post DP, and 24 bits pre DP.
#endif

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace ParkTransform
{



	#if(config_PRINT_DEBUG_PARK_TRANSFORM == 1)
		//! Debug buffer
		static char _debugBuff[100] = {0};
	#endif

	#if(config_ENABLE_FIXED_POINT_FUNCTIONS == 1)
		fp<CDP> _sinLut[configPARK_LUT_SIZE] = {(int32_t)0};
		fp<CDP> _cosLut[configPARK_LUT_SIZE] = {(int32_t)0};
	#endif

	//===============================================================================================//
	//=====================================  METHOD DEFINITIONS =====================================//
	//===============================================================================================//

	//! @brief		Initialisation routines. Populates sin and cos LUT's.
	//!				Call before calling any other functions in ParkTransform.
	//! @note		Not thread-safe. Call from one task only.
	//! @public		
	void Transformer::Init()
	{
		#if(config_ENABLE_FIXED_POINT_FUNCTIONS == 1)

			uint16_t i;

			#if(config_PRINT_DEBUG_PARK_TRANSFORM == 1)
				UartDebug::PutString("PARK: Start of sin LUT values:\r\n");
			#endif

			for(i = 0; i < configPARK_LUT_SIZE; i++)
			{
				_sinLut[i] = fp<CDP>(sin(((double)i/(double)configPARK_LUT_SIZE)*2.0*PI));
				#if(config_PRINT_DEBUG_PARK_TRANSFORM == 1)
					snprintf(_debugBuff, sizeof(_debugBuff), " %f,", Fix2Float<CDP>(_sinLut[i].intValue));
					UartDebug::PutString(_debugBuff);
				#endif
			}

			#if(config_PRINT_DEBUG_PARK_TRANSFORM == 1)
				UartDebug::PutString("\r\nPARK: End of sin LUT values.\r\n");
			#endif

			#if(config_PRINT_DEBUG_PARK_TRANSFORM == 1)
				UartDebug::PutString("PARK: Start of cos LUT values:\r\n");
			#endif

			for(i = 0; i < configPARK_LUT_SIZE; i++)
			{
				_cosLut[i] = fp<CDP>(cos(((double)i/(double)configPARK_LUT_SIZE)*2.0*PI));
				#if(config_PRINT_DEBUG_PARK_TRANSFORM == 1)
					snprintf(_debugBuff, sizeof(_debugBuff), " %f,", Fix2Float<CDP>(_cosLut[i].intValue));
					UartDebug::PutString(_debugBuff);
				#endif
			}

			#if(config_PRINT_DEBUG_PARK_TRANSFORM == 1)
				UartDebug::PutString("\r\nPARK: End of cos LUT values.\r\n");
			#endif

		#endif // #if(config_ENABLE_FIXED_POINT_FUNCTIONS == 1)
	}

	void Transformer::Forward(double alpha, double beta, double theta, double *d, double *q)
	{
		// d = alpha*cos(theta) + beta*sin(theta)
		// q = beta*cos(theta) - alpha*sin(theta)
		*d = alpha*cos(theta) + beta*sin(theta);
		*q = beta*cos(theta) - alpha*sin(theta);
	}

	void Transformer::Inverse(
		double d,
		double q,
		double theta,
		double *alpha,
		double *beta)
	{
		// alpha = d*cos(theta) - q*sin(theta)
		// beta  = q*cos(theta) + d*sin(theta)
		*alpha= d*cos(theta) - q*sin(theta);
		*beta = q*cos(theta) + d*sin(theta);
	}

	#if(config_ENABLE_FIXED_POINT_FUNCTIONS == 1)
		void Transformer::Forward(fp<CDP> alpha, fp<CDP> beta, fp<CDP> theta,
			fp<CDP> *d, fp<CDP> *q)
		{
			// Angle rounded to nearest degree
			//! @todo Fix this loss in precision
			*d = (alpha*_cosLut[theta.intValue>>CDP]) + (beta*_sinLut[theta.intValue>>CDP]);

			#if(config_PRINT_DEBUG_PARK_TRANSFORM == 1)
				snprintf(_debugBuff, sizeof(_debugBuff), "PARK: sin(theta) = %f, cos(theta) = %f\r\n",
					Fix2Float<CDP>(_sinLut[theta.intValue>>CDP].intValue), Fix2Float<CDP>(_cosLut[theta.intValue>>CDP].intValue));
				UartDebug::PutString(_debugBuff);
			#endif

			*q = (beta*_cosLut[theta.intValue>>CDP]) - (alpha*_sinLut[theta.intValue>>CDP]);
		}
		
		void Transformer::Inverse(
				fp<CDP> d,
				fp<CDP> q,
				fp<CDP> theta,
				fp<CDP> *alpha,
				fp<CDP> *beta)
		{

			*alpha= d*_cosLut[theta.intValue>>CDP] - q*_sinLut[theta.intValue>>CDP];
			*beta = q*_cosLut[theta.intValue>>CDP] + d*_sinLut[theta.intValue>>CDP];
		}

	#endif // #if(config_ENABLE_FIXED_POINT_FUNCTIONS == 1)

} // namespace ParkTransform

// EOF
