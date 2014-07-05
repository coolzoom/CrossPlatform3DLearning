/*
 * Image.cpp
 *
 *  Created on: 2 Jul 2014
 *      Author: Dimitri Kourkoulis
 */

#include "Image.h"
#include <png.h>
#include <stdio.h>
#include "GameException.h"

using namespace std;

namespace AvoidTheBug3D {

Image::Image(string fileLocation, const boost::shared_ptr<Configuration>& cfg,
		const boost::shared_ptr<GameLog>& log) {
	this->cfg = cfg;
	this->log = log;

	this->loadFromFile(fileLocation);

}

Image::~Image() {
	// TODO Auto-generated destructor stub
}

void Image::loadFromFile(string fileLocation) {
	FILE *fp = fopen((cfg->getHomeDirectory() + fileLocation).c_str(), "fb");

	if (!fp) {
		throw GameException(
				"Could not open file " + cfg->getHomeDirectory()
						+ fileLocation);
	}

	fclose(fp);
}

}

