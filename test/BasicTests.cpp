//!
//! @file 			BaiscTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2014/01/21
//! @last-modified 	2014/01/21
//! @brief			Basic Park transformation tests.
//! @details
//!					See README.rst in root dir for more info.

#include "../api/ParkTransform.hpp"

#include "../lib/UnitTest++/src/UnitTest++.h"

namespace ParkTransformTest
{
	SUITE(BaiscTests)
	{

		TEST(BasicTest1)
		{
			ParkTransform::Transformer parkTransformer;

			double d;
			double q;

			// When alpha=0.0, beta=0.0, theta=0.0 then d=0.0, q=0.0
			parkTransformer.Forward(0.0, 0.0, 0.0, &d, &q);
			CHECK_CLOSE(0.0, d, 0.05);
			CHECK_CLOSE(0.0, q, 0.05);
		}
		
		TEST(BasicTest2)
		{
			ParkTransform::Transformer parkTransformer;

			double d;
			double q;

			// When alpha=1.0, beta=1.0, theta=0 then d=1, q=1
			parkTransformer.Forward(1.0, 1.0, 0.0, &d, &q);
			CHECK_CLOSE(1.0, d, 0.05);
			CHECK_CLOSE(1.0, q, 0.05);
		}

	} // SUITE(BaiscTests)
} // namespace ParkTransformTest
