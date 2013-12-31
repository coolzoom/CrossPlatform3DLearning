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
#define LOGINFO(MESSAGE) log->append(info, MESSAGE);
#define LOGERROR(MESSAGE) log->append(error, MESSAGE);

#ifdef GAMELOGDEBUG
#define LOGDEBUG(MESSAGE) log->append(debug, MESSAGE);
#else
#define LOGDEBUG(MESSAGE)
#endif

#include <iostream>

using namespace std;

namespace AvoidTheBug3D {

/**
 * Possible logging levels
 */
enum GameLogLevel {
	info, debug, error
};

class GameLog {
public:
	/**
	 * Default constructor
	 */
	GameLog();

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
