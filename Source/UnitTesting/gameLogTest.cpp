/*
 * gameLogTest.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: Dimitrios Kourkoulis
 */
#include <boost/test/unit_test.hpp>

#ifdef DEBUG
#undef DEBUG
#endif

#ifdef _DEBUG
#undef _DEBUG
#endif

#include "../GameLog.h"
#include <sstream>

using namespace std;

using namespace AvoidTheBug3D;
BOOST_AUTO_TEST_SUITE(GameLogTestSuite)
BOOST_AUTO_TEST_CASE( gameLogTest )
{

	ostringstream oss;

	GameLog *log = new GameLog(oss);

	LOGINFO("It works");
	BOOST_CHECK_EQUAL(oss.str().find("It works") != (string::npos), true);

	LOGDEBUG("This should not appear")
	BOOST_CHECK_EQUAL(oss.str().find("This should not appear") == (string::npos), true);

	delete log;
}
BOOST_AUTO_TEST_SUITE_END()
