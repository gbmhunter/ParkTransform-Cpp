//!
//! @file 			Transformer.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 		n/a
//! @created		2012/10/10
//! @last-modified 	2014/01/21
//! @brief 			Header file for ParkTransform.cpp
//! @details
//!					See README.rst

//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef PARK_TRANSFORM_TRANSFORMER_H
#define PARK_TRANSFORM_TRANSFORMER_H

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace ParkTransform
{

	class Transformer
	{

	public:
		//===============================================================================================//
		//===================================== PUBLIC METHOD PROTOTYPES ================================//
		//===============================================================================================//

		void Init();

		//! @brief 		Converts from stationary alpha-beta to rotating d-q reference frame
		//! @warning	Slow! Uses doubles and sin function
		//! @note		Thread-safe.
		//! @public
		void Forward(double alpha, double beta, double theta,
			double *d, double *q);

		//! @brief 		Converts from rotating d-q reference frame to stationary alpha-beta
		//! @details
		//! @warning	Slow! Uses doubles and sin function
		//! @public
		void Inverse(double d, double q, double theta,
			double *alpha, double *beta);

		#if(config_ENABLE_FIXED_POINT_FUNCTIONS == 1)
			//! @brief 		Converts from stationary alpha-beta to rotating d-q reference frame.
			//! @details 	Uses fixed-point numbers and sin/cos LUT's. Call ParkTransform::Init() before
			//!				calling this function.							\n
			//! 			Maths:											\n
			//!						d = alpha*cos(theta) + beta*sin(theta)	\n
			//! 					q = beta*cos(theta) - alpha*sin(theta)	\n
			//!	@note		Execution Time: 192 clock cycles (4us @ 48MHz) (including function call)
			//! @note		Thread-safe.
			//! @public
			void Forward(
				Fp::fp<CDP> alpha,
				Fp::fp<CDP> beta,
				Fp::fp<CDP> theta,
				fp<CDP> *d,
				fp<CDP> *q);

			//! @brief 		Converts from rotating d-q reference frame to stationary alpha-beta
			//! @details	Uses fixed-point mathematics.
			//!				Call ParkTransform::Init() before calling this function.	\n
			//!					Maths:									\n
			//!					alpha = d*cos(theta) - q*sin(theta)		\n
			//! 				beta  = q*cos(theta) + d*sin(theta)		\n
			//! @note		Execution Time: 144 clock cycles (3us @ 48MHz) (including function call)
			//! @note		Thread-safe
			//! @public
			void Inverse(
				Fp::fp<CDP> d,
				Fp::fp<CDP> q,
				Fp::fp<CDP> theta,
				Fp::fp<CDP> *alpha,
				Fp::fp<CDP> *beta);
		#endif

	};

	//===============================================================================================//
	//====================================== INLINE FUNCTIONS =======================================//
	//===============================================================================================//
		
	// none

	//===============================================================================================//
	//====================================== PUBLIC VARIABLES =======================================//
	//===============================================================================================//

	// none

} // namespace ParkTransform

#endif // #ifndef PARK_TRANSFORM_TRANSFORMER_H

// EOF
