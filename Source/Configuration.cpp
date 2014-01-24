/*
 * Configuration.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: me
 */

#include "Configuration.h"

#include <boost/filesystem.hpp>

namespace AvoidTheBug3D {

Configuration::Configuration() {
	// TODO Auto-generated constructor stub

}

Configuration::~Configuration() {
	// TODO Auto-generated destructor stub
}

string Configuration::getHomeDirectory() {
	boost::filesystem::path current;
	current = boost::filesystem::current_path();
	return string(current.c_str());
}


} /* namespace AvoidTheBug3D */

