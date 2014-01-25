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
#include <boost/smart_ptr.hpp>

using namespace AvoidTheBug3D;
using namespace std;

BOOST_AUTO_TEST_SUITE(ModelTestSuite)
BOOST_AUTO_TEST_CASE( home_directory_test ) {

	GameLog *logPtr = new GameLog(cout);
	boost::scoped_ptr<GameLog> log(logPtr);

	Configuration *confPtr = new Configuration();
	boost::scoped_ptr<Configuration> conf(confPtr);

	LOGINFO(conf->getHomeDirectory());
}
BOOST_AUTO_TEST_SUITE_END()
