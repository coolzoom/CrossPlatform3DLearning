#pragma once

/*
 * Image.h
 *
 *  Created on: 2 Jul 2014
 *      Author: Dimitri Kourkoulis
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include <boost/smart_ptr.hpp>
#include "GameLog.h"
#include "Configuration.h"
#include <png.h>

using namespace std;

namespace AvoidTheBug3D {

class Image {
private:
	// Configuration & logging objects
	boost::shared_ptr<Configuration> cfg;
	boost::shared_ptr<GameLog> log;

	int width, height;
	png_byte colorType;
	png_byte bitDepth;
	int numberOfPasses;

	// Load image from a .png file
	void loadFromFile(string fileLocation);

public:
	Image(string fileLocation, const boost::shared_ptr<Configuration> &cfg,
			const boost::shared_ptr<GameLog> &log);

	virtual ~Image();
};

}
#endif /* IMAGE_H_ */
