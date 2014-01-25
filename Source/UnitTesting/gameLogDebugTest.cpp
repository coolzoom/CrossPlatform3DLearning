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
#include <boost/smart_ptr.hpp>

using namespace std;

using namespace AvoidTheBug3D;
BOOST_AUTO_TEST_SUITE(GameLogDebugTestSuite)
BOOST_AUTO_TEST_CASE( gameLogDebugTest )
{
	ostringstream oss;

	GameLog *logPtr = new GameLog(oss);
	boost::scoped_ptr<GameLog> log(logPtr);

	LOGINFO("It works");
	BOOST_CHECK_EQUAL(oss.str().find("It works") != (string::npos), true);

	LOGDEBUG("This should appear");
	BOOST_CHECK_EQUAL(oss.str().find("This should appear") != (string::npos), true);

}
BOOST_AUTO_TEST_SUITE_END()
