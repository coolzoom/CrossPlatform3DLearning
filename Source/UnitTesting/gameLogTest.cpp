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
#include <boost/smart_ptr.hpp>

using namespace std;

using namespace AvoidTheBug3D;
BOOST_AUTO_TEST_SUITE(GameLogTestSuite)
BOOST_AUTO_TEST_CASE( gameLogTest ) {
	ostringstream oss;

	GameLog *logPtr = new GameLog(oss);
	boost::scoped_ptr<GameLog> log(logPtr);

	LOGINFO("It works");
	BOOST_CHECK_EQUAL(oss.str().find("It works") != (string::npos), true);

	LOGERROR("Error test");
	BOOST_CHECK_EQUAL(oss.str().find("Error test") != (string::npos), true);

	LOGDEBUG("This should not appear");
	BOOST_CHECK_EQUAL(
			oss.str().find("This should not appear") == (string::npos), true);

}
BOOST_AUTO_TEST_SUITE_END()
