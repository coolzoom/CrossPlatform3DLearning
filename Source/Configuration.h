/*
 * Configuration.h
 *
 *  Created on: Jan 19, 2014
 *      Author: me
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>

using namespace std;

namespace AvoidTheBug3D {

class Configuration {
public:
	/**
	 * Default constructor
	 */
	Configuration();

	/**
	 * Destructor
	 */
	virtual ~Configuration();

	/**
	 * Get the home directory of the application
	 * @return The home diractory
	 */
	string getHomeDirectory();
};

} /* namespace AvoidTheBug3D */

#endif /* CONFIGURATION_H_ */
