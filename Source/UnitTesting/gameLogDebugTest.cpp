/*
 * gameLogDebugTest.cpp
 *
 *  Created on: Jan 7, 2014
 *      Author: Dimitrios Kourkoulis
 */
#include <boost/test/unit_test.hpp>
#if not defined(DEBUG) && not defined(_DEBUG)
#define DEBUG
#endif
#include "../GameLog.h"
#include <sstream>

using namespace std;

using namespace AvoidTheBug3D;
BOOST_AUTO_TEST_SUITE(GameLogDebugTestSuite)
BOOST_AUTO_TEST_CASE( gameLogDebugTest )
{
	ostringstream oss;

	GameLog *log = new GameLog(oss);

	LOGINFO("It works");
	BOOST_CHECK_EQUAL(oss.str().find("It works") != (string::npos), true);

	LOGDEBUG("This should appear");
	BOOST_CHECK_EQUAL(oss.str().find("This should appear") != (string::npos), true);

	delete log;
}
BOOST_AUTO_TEST_SUITE_END()
