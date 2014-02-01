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

Configuration::Configuration(boost::shared_ptr<GameLog> log) {
	this->log = log;
	LOGINFO("Configuration object initialised");
	this->findHomeDirectory();
}

Configuration::~Configuration() {
	LOGINFO("Configuration object being destroyed");
}

string Configuration::getHomeDirectory() {
	return homeDirectory;
}

void Configuration::findHomeDirectory() {
	boost::filesystem::path homePath = boost::filesystem::current_path();
	string currentLower = homePath.generic_string();
	transform(currentLower.begin(), currentLower.end(), currentLower.begin(),
			::tolower);

	if (boost::algorithm::ends_with(currentLower, "unittesting")) // Linux unit testing
			{
		homePath = homePath.branch_path().branch_path();
	} else if (boost::algorithm::ends_with(currentLower, "temp")) // Linux IDE execution
			{
		homePath = homePath.branch_path();
	} else if (boost::algorithm::ends_with(currentLower, "debug")
			|| boost::algorithm::ends_with(currentLower, "release")) // Windows
					{
		if (currentLower.find("unittesting")) // Unit testing
				{
			homePath = homePath.branch_path().branch_path().branch_path();
		} else // IDE execution
		{
			homePath = homePath.branch_path().branch_path();
		}
	} else if (boost::algorithm::ends_with(currentLower, "bin")) // production
			{
		homePath = homePath.branch_path();
	} else // if no conditions is met, the home directory cannot be determined
	{
		throw GameException("Could not determine the home directory");
	}

	this->homeDirectory = homePath.generic_string();
	LOGINFO("Configuration: found home directory: " + homeDirectory);
}

} /* namespace AvoidTheBug3D */

