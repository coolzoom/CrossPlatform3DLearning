/*
 * gameLogTest.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: Dimitrios Kourkoulis
 */
#include <boost/test/unit_test.hpp>
#include "../GameLog.h"
#include <iostream>

using namespace std;

using namespace AvoidTheBug3D;
BOOST_AUTO_TEST_SUITE(GameLogTestSuite)
BOOST_AUTO_TEST_CASE( gameLogTest )
{
	GameLog *log = new GameLog(cout);
	LOGINFO("It works");
	delete log;
}
BOOST_AUTO_TEST_SUITE_END()
