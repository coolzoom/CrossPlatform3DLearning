/*
 * Configuration.h
 *
 *  Created on: Jan 19, 2014
 *      Author: Dimitri Kourkoulis
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>
#include <boost/smart_ptr.hpp>
#include "GameLog.h"

using namespace std;

namespace AvoidTheBug3D {

class Configuration {
private:
	boost::shared_ptr<GameLog> log;
	string homeDirectory;
	void findHomeDirectory();
public:
	/**
	 * Constructor
	 */
	Configuration(boost::shared_ptr<GameLog> log);

	/**
	 * Destructor
	 */
	virtual ~Configuration();

	/**
	 * Get the home directory of the application
	 * @return The home directory
	 */
	string getHomeDirectory();
};

} /* namespace AvoidTheBug3D */

#endif /* CONFIGURATION_H_ */
