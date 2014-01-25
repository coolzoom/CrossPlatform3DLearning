/*
 * Configuration.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: Dimitri Kourkoulis
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
	boost::filesystem::path homePath = boost::filesystem::current_path();
    string currentLower = string(homePath.c_str());
    transform(currentLower.begin(), currentLower.end(), currentLower.begin(), ::tolower);
    string homeDirectory;
    if (boost::algorithm::ends_with(currentLower, "unittesting")) // Linux unit testing
    {
    	homePath = homePath.branch_path().branch_path();
    }
    else if (boost::algorithm::ends_with(currentLower, "temp")) // Linux IDE execution
    {
    	homePath = homePath.branch_path();
    }
    else if (boost::algorithm::ends_with(currentLower, "debug") ||
    		boost::algorithm::ends_with(currentLower, "release")) // Windows
    {
    	if (currentLower.find("unittesting")) // Unit testing
    	{
    		homePath = homePath.branch_path().branch_path().branch_path();
    	}
    	else // IDE execution
    	{
    		homePath = homePath.branch_path().branch_path();
    	}
    }
    else if (boost::algorithm::ends_with(currentLower, "bin")) // production
    {
    	homePath = homePath.branch_path();
    }
    else // if no conditions is met, the home directory cannot be determined
    {
    	throw GameException("Could not determine the home directory");
    }
	return string(homePath.c_str());
}


} /* namespace AvoidTheBug3D */

