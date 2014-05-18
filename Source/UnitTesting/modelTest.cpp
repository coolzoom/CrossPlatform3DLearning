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
//BOOST_AUTO_TEST_CASE( model_test ) {
//
//	GameLog *logPtr = new GameLog(cout);
//	boost::shared_ptr<GameLog> log(logPtr);
//
//	Configuration *cfgPtr = new Configuration(log);
//	boost::shared_ptr<Configuration> cfg(cfgPtr);
//
//	Model *modelPtr = new Model(
//			"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithNormals.obj", false, true,
//			cfg, log);
//	boost::scoped_ptr<Model> model(modelPtr);
//
//	BOOST_CHECK_EQUAL(model->getNumVertices() > 0, true);
//	BOOST_CHECK_EQUAL(model->getNumFaces() > 0, true);
//
//	model->getVertexData();
//	model->getIndexData();
//	model->getNormalsData();
//	model->getNormalsIndexData();
//
//	cout << "Normals count: " << model->getNormalsIndexDataIndexCount() << endl
//			<< "Index count: " << model->getIndexDataIndexCount() << endl;
//	BOOST_CHECK_EQUAL(model->getNormalsIndexDataIndexCount(),
//			model->getIndexDataIndexCount());
//
//}
BOOST_AUTO_TEST_SUITE_END()
