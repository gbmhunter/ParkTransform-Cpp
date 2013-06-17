//!
//! @file 		ParkTransform.hpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		10/10/2012
//! @brief 		Header file for ParkTransform.cpp
//! @details
//!				See README.rst

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