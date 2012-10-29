//!
//! @file 		ParkTransform.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		10/10/2012
//! @brief 		Header file for ParkTransform.cpp
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

//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef _PARK_TRANSFORM_H
#define _PARK_TRANSFORM_H

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace ParkTransform
{

using namespace FixedP;

//===============================================================================================//
//=================================== PUBLIC FUNCTION PROTOTYPES ================================//
//===============================================================================================//

// See the function definitions in ParkTransform.cpp for more information

void Init();
void Forward(fp<CDP> alpha, fp<CDP> beta, fp<CDP> theta, 
	fp<CDP> *d, fp<CDP> *q);
void Forward(double alpha, double beta, double theta, 
	double *d, double *q);
void Inverse(fp<CDP> d, fp<CDP> q, fp<CDP> theta, 
	fp<CDP> *alpha, fp<CDP> *beta);
void Inverse(double d, double q, double theta, 
	double *alpha, double *beta);
	
//===============================================================================================//
//====================================== INLINE FUNCTIONS =======================================//
//===============================================================================================//
	
// none

//===============================================================================================//
//====================================== PUBLIC VARIABLES =======================================//
//===============================================================================================//

// none

} // namespace ClarkTransform

#endif // #ifndef _PARK_TRANSFORM_H

// EOF