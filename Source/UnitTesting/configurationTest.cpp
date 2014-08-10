/*
 * configurationTest.cpp
 *
 *  Created on: Jan 24, 2013
 *      Author: Dimitri Kourkoulis
 */
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../GameLog.h"
#include "../Configuration.h"
#include <boost/smart_ptr.hpp>
#include <algorithm>
#include <boost/algorithm/string/predicate.hpp>


using namespace AvoidTheBug3D;
using namespace std;

BOOST_AUTO_TEST_SUITE(ModelTestSuite)
BOOST_AUTO_TEST_CASE( home_directory_test ) {

	GameLog *logPtr = new GameLog(cout);
	boost::shared_ptr<GameLog> log(logPtr);

	Configuration *confPtr = new Configuration(log);
	boost::scoped_ptr<Configuration> conf(confPtr);

	string homeDirectory = conf->getHomeDirectory();
	transform(homeDirectory.begin(), homeDirectory.end(), homeDirectory.begin(),
				::tolower);
	BOOST_CHECK_EQUAL(boost::algorithm::ends_with(homeDirectory, "crossplatform3dlearning"), true);

}
BOOST_AUTO_TEST_SUITE_END()
