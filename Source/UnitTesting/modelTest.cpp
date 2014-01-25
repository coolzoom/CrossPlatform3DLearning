/*
 * modelTest.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: Dimitrios Kourkoulis
 */
#include <boost/test/unit_test.hpp>
#include "../Model.h"
#include "../GameLog.h"
#include "../Configuration.h"

using namespace AvoidTheBug3D;
BOOST_AUTO_TEST_SUITE(ModelTestSuite)
BOOST_AUTO_TEST_CASE( model_test ) {
	Model *gc = new Model();
	Configuration *cfg = new Configuration();
	gc->loadFromFile(cfg->getHomeDirectory() + "/Game/Data/UnspecifiedAnimal/UnspecifiedAnimal.obj" );
	gc->outputVertices();

	delete cfg;
	delete gc;

	BOOST_CHECK(1 == 1);
	BOOST_REQUIRE(1 == 1);
	BOOST_CHECK_MESSAGE(1 == 2, "Ooops! Just testing :)");

	BOOST_ERROR("Testing again");
	//BOOST_FAIL("Testing FAIL, and here it stops");
	//BOOST_CHECK_MESSAGE(1 == 2,
		//	"This should not appear (execution stops on BOOST_FAIL)");
}
BOOST_AUTO_TEST_SUITE_END()





