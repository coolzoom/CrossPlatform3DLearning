/*
 * Configuration.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: me
 */

#include "Configuration.h"

#include <boost/filesystem.hpp>
#include <algorithm>
#include <boost/algorithm/string/predicate.hpp>
#include "GameException.h"

using namespace std;

namespace AvoidTheBug3D {

Configuration::Configuration() {
	// TODO Auto-generated constructor stub

}

Configuration::~Configuration() {
	// TODO Auto-generated destructor stub
}

string Configuration::getHomeDirectory() {
	string current = string(boost::filesystem::current_path().c_str());
    string currentLower = current;
    transform(currentLower.begin(), currentLower.end(), currentLower.begin(), ::tolower);
    string homeDirectory;
    if (boost::algorithm::ends_with(currentLower, "unittesting")) // Linux unit testing
    {

    }
    else if (boost::algorithm::ends_with(currentLower, "temp")) // Linux IDE execution
    {

    }
    else if (boost::algorithm::ends_with(currentLower, "debug") ||
    		boost::algorithm::ends_with(currentLower, "release")) // Windows
    {
    	if (currentLower.find("unittesting")) // Unit testing
    	{

    	}
    	else // IDE execution
    	{

    	}
    }
    else if (boost::algorithm::ends_with(currentLower, "bin")) // production
    {

    }
    else // if no conditions is met, the home directory cannot be determined
    {
    	throw GameException("Could not determine the home directory");

    }
	return homeDirectory;
}


} /* namespace AvoidTheBug3D */

