//!
//! @file 				Config.hpp
//! @project			park-transform-cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 			n/a
//! @created			2014/01/21
//! @last-modified 		2014/01/21
//! @brief 				Configuration file for park-transform-cpp library.
//! @details
//!						See the README in the repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef PARK_TRANSFORM_CONFIG_H
#define PARK_TRANSFORM_CONFIG_H

//! @brief		Set to 1 to print debug messages
#define config_PRINT_DEBUG_PARK_TRANSFORM		0

#define CDP				8

//! @brief		The size of the sine and cosine LUT's. A higher number gives higher precision but uses more memory (RAM).
#define configPARK_LUT_SIZE					(255)

//! @brief		Set to 1 to enable fixed-point transform functions.
//! @note		The fixed-point-cpp library is required.
#define config_ENABLE_FIXED_POINT_FUNCTIONS		0


#endif // #define PARK_TRANSFORM_CONFIG_H

// EOF
