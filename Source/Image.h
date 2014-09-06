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


/// Image loading class. Only handles RGB encoded data in PNG files for now.
class Image {
private:
	// Configuration & logging objects
	boost::shared_ptr<Configuration> cfg;
	boost::shared_ptr<GameLog> log;

	int width, height;
	float* imageData;

	// Load image from a .png file
	void loadFromFile(const string &fileLocation);

public:
	/**
	 * Constructor
	 * @param fileLocation Location of image file
	 * @param cfg Game configuration object
	 * @param log Game log
	 */
	Image(const string &fileLocation, const boost::shared_ptr<Configuration> cfg,
			const boost::shared_ptr<GameLog> log);

	/**
	 * Destructor
	 */
	virtual ~Image();

	/**
	 * Get the image width
	 * @return The image width
	 */
	int getWidth() const;

	/**
	 * Get the image height
	 * @return The image height
	 */
	int getHeight() const;

	/**
	 * Get the image data
	 * @return The image data
	 */
	float* getData() const;

};

}
#endif /* IMAGE_H_ */
