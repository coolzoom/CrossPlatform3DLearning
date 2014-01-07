/*
 * GameLog.h
 *
 *  Created on: Dec 30, 2013
 *      Author: Dimitri Kourkoulis
 */

#ifndef GAMELOG_H_
#define GAMELOG_H_

/**
 * Logging is accessed through macros so that it can be completely
 * omitted if deactivated.
 */

#define LOGERROR(MESSAGE) log->append(error, MESSAGE);

#define LOGINFO(MESSAGE) log->append(info, MESSAGE);

#if defined(DEBUG) || defined(_DEBUG)
#define LOGDEBUG(MESSAGE) log->append(debug, MESSAGE);
#else
#define LOGDEBUG(MESSAGE)
#endif

#include <ostream>

using namespace std;

namespace AvoidTheBug3D {

/**
 * Possible logging levels
 */
enum GameLogLevel {
	info, debug, error
};

class GameLog {
private:
	ostream *logStream;
public:
	/**
	 * Default constructor
	 */
	GameLog(ostream &stream);

	/**
	 * Destructor
	 */
	virtual ~GameLog();

	/**
	 * Append a message to the log
	 * @param level The error level of the message
	 * @param message The message
	 */
	void append(const GameLogLevel level, const string message);
};
}

#endif /* GAMELOG_H_ */
