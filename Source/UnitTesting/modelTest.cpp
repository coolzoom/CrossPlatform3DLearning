/*
 * modelTest.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: Dimitrios Kourkoulis
 */
#include <boost/test/unit_test.hpp>
#include "../Model.h"
#include "../GameLog.h"

using namespace AvoidTheBug3D;
BOOST_AUTO_TEST_SUITE(ModelTestSuite)
BOOST_AUTO_TEST_CASE( my_test ) {
	Model *gc = new Model();
#ifdef _WIN32
	gc->loadFromFile("../../../Game/Data/UnspecifiedAnimal/UnspecifiedAnimal.obj");
#else
	gc->loadFromFile("../../Game/Data/UnspecifiedAnimal/UnspecifiedAnimal.obj");
#endif
	gc->outputVertices();
	delete gc;

	BOOST_CHECK(1 == 1);
	BOOST_REQUIRE(1 == 1);
	BOOST_CHECK_MESSAGE(1 == 2, "Ooops! Just testing :)");
	BOOST_CHECK_EQUAL(2, 1);
	BOOST_ERROR("Testing again");
	//BOOST_FAIL("Testing FAIL, and here it stops");
	//BOOST_CHECK_MESSAGE(1 == 2,
		//	"This should not appear (execution stops on BOOST_FAIL)");
}
BOOST_AUTO_TEST_SUITE_END()





