============================
Park Transformation Library
============================

- Author: gbmhunter <gbmhunter@gmail.com> (http://www.cladlab.com)
- Created: 2012/10/10
- Last Modified: 2014/01/21
- Version: v2.0.0.0
- Company: CladLabs
- Project: n/a
- Language: C++
- Compiler: GCC	
- uC Model: All
- Computer Architecture: All
- Operating System: n/a
- Documentation Format: Doxygen
- License: GPLv3

Description
-----------

Library for performing the Park transformation, a mathematical transformation commonly used for BLDC motor control.

Can be used with either standard doubles, or a fixed-point variable type. The fixed-point functions use sine/cosine LUT's (fast), while the double functions use sin() and cos() functions provided by math.h in the standard C library (slow).

Dependencies
---------------------
	
The following table lists all of park-transform-cpp's dependencies.

====================== ==================== ======================================================================
Dependency             Delivery             Usage
====================== ==================== ======================================================================
<stdio.h>              Standard C library   snprintf()
<math.h>               Standard C library
"FixedPoint.hpp"       /lib/fixed-point-cpp Fixed point transform functions (faster than doubles/floats especially when system has no floating point unit).
====================== ==================== ======================================================================


Usage
-----

::
	
	Coming soon.
	
See `test/ParkTransformTest.cpp` for more examples.
	
Issues
------

See the GitHub issues section.
	
Changelog
---------

======== ========== ==========================================================================================================
Version  Date       Comment
======== ========== ==========================================================================================================
v2.0.0.0 2014/01/21 Added Makefile, closes #8. Added automatic dependency generation, closes #14. Added unit tests, closes #7. Added config file, closes #18. Make fixed-point functions optional via pre-compiler macros, closes #17. Removed unneccessary includes from code files, closes #11. Converted functions into methods of new class 'Transformer', closes #9. Moved function descriptions to .hpp file, closes #6. Header guard comment fixed, closes #5. Removed _ prefix from header guards, closes #4.
v1.1.0.0 2014/01/21 Moved and renamed code files to follow new file format, closes #15. Created Eclipse project files for library, closes #16.
v1.0.2.0 2013/06/17 Removed unnecessary includes from .cpp file. Removed '_' from header guard. Change Clark comment to Park.
v1.0.1.0 2013/06/17 Deleted .hgignore file. Renamed header to .hpp and moved into 'src/include'.
v1.0.0.1 2013/06/08 README now in table format.
v1.0.0.0 2013/06/03 First versioned commit. Added README.rst. Moved code into 'src' folder.
======== ========== ==========================================================================================================