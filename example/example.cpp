//!
//! @file 			example.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created 		2014/01/21
//! @last-modified 	2014/01/21
//! @brief 			Example Park transform program, designed to be run on Linux.
//! @details
//!				See README.rst in root dir for more info.

#include <stdio.h>
#include <iostream>
#include <string>

#include "../api/ParkTransform.hpp"


using namespace std;


int main()
{
	
	//============ SETUP DEFAULT COMMAND GROUP ==========//

	//rxController.defaultCmdGroup = &cmdGroupUser;

	while(1)
	{
		char inputMsg[30];

		cin.get(inputMsg, 30);
		cin.ignore();

		// Run rx controller
		//rxController.Run(inputMsg);
	}
}
