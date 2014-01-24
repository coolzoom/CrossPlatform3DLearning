/*
 * modelTest.cpp
 *
 *  Created on: Jan 24, 2013
 *      Author: Dimitri Kourkoulis
 */
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../GameLog.h"
#include "../Configuration.h"

using namespace AvoidTheBug3D;
using namespace std;

BOOST_AUTO_TEST_SUITE(ModelTestSuite)
BOOST_AUTO_TEST_CASE( home_directory_test ) {
	GameLog *log = new GameLog(cout);
	Configuration *conf = new Configuration();
	LOGINFO(conf->getHomeDirectory());
	delete conf;
	delete log;
}
BOOST_AUTO_TEST_SUITE_END()
