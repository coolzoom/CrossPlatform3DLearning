/*
* boundingBoxesTest.cpp
*
*  Created on: Oct 11, 2014
*      Author: Dimitri Kourkoulis
*/
#include <boost/test/unit_test.hpp>
#include "../GameLog.h"
#include "../Configuration.h"
#include <boost/smart_ptr.hpp>
#include "../BoundingBoxes.h"

using namespace AvoidTheBug3D;
using namespace std;

BOOST_AUTO_TEST_SUITE(ModelTestSuite)
	BOOST_AUTO_TEST_CASE( bounding_boxes_directory_test ) {

		boost::shared_ptr<GameLog> log(new GameLog(cout));

		boost::shared_ptr<Configuration> cfg(new Configuration(log));

		boost::scoped_ptr<BoundingBoxes> bboxes(new BoundingBoxes(cfg, log));

		bboxes->loadFromFile("/Game/Data/GoatBB/goatBB.obj");

		BOOST_CHECK_EQUAL(bboxes->vertices->size(), 16);
		BOOST_CHECK_EQUAL(bboxes->facesVertexIndexes->size(), 12);

		cout<<"Bounding boxes vertices: "<<endl;
		for (int idx = 0; idx < 16; idx++)
		{
			cout<<bboxes->vertices->at(idx)[0] << ", " <<
				bboxes->vertices->at(idx)[1] << ", " <<
				bboxes->vertices->at(idx)[2] << ", " << endl;

		}

		cout<<"Bounding boxes faces vertex indexes: "<<endl;
		for (int idx = 0; idx < 12; idx++)
		{
			cout<<bboxes->facesVertexIndexes->at(idx)[0] << ", " <<
				bboxes->facesVertexIndexes->at(idx)[1] << ", " <<
				bboxes->facesVertexIndexes->at(idx)[2] << ", " <<
				bboxes->facesVertexIndexes->at(idx)[3] << ", " << endl;

		}
}
BOOST_AUTO_TEST_SUITE_END()
