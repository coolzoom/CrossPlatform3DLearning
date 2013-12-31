/*
 * GameLog.cpp
 *
 *  Created on: Dec 30, 2013
 *      Author: Dimitrios Kourkoulis
 */

#include "GameLog.h"
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

namespace AvoidTheBug3D {

GameLog::GameLog() {
	// TODO Auto-generated constructor stub

}

GameLog::~GameLog() {
	// TODO Auto-generated destructor stub
}

void GameLog::append(const GameLogLevel level, const string message) {

	ostringstream dateTimeOstringstream;
	const boost::posix_time::ptime now =
			boost::posix_time::second_clock::local_time();
	boost::posix_time::time_facet* const f = new boost::posix_time::time_facet(
			"%Y-%m-%d %T");
	dateTimeOstringstream.imbue(std::locale(dateTimeOstringstream.getloc(), f));
	dateTimeOstringstream << now;

	string indicator;
	switch (level) {
	case info:
		indicator = "INFO";
		break;
	case debug:
		indicator = "DEBUG";
		break;
	case error:
		indicator = "ERROR";
		break;
	default:
		indicator = "";
		break;
	}

	cout << dateTimeOstringstream.str().c_str() << " - " << indicator << ": " << message.c_str() << endl;
}

} /* namespace AvoidTheBug3D */
