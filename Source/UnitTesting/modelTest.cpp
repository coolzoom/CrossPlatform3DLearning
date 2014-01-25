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
#include <boost/smart_ptr.hpp>

using namespace AvoidTheBug3D;
BOOST_AUTO_TEST_SUITE(ModelTestSuite)
BOOST_AUTO_TEST_CASE( model_test ) {

	Model *modelPtr = new Model();
	boost::scoped_ptr<Model> model(modelPtr);

	GameLog *logPtr = new GameLog(cout);
	boost::shared_ptr<GameLog> log(logPtr);

	Configuration *cfgPtr = new Configuration(log);
	boost::scoped_ptr<Configuration> cfg(cfgPtr);

	model->loadFromFile(cfg->getHomeDirectory() + "/Game/Data/UnspecifiedAnimal/UnspecifiedAnimal.obj" );

	BOOST_CHECK_EQUAL(model->getNumVertices() > 0, true);

}
BOOST_AUTO_TEST_SUITE_END()
