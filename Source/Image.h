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
#include <pngstruct.h> // needed by pnginfo.h
#include <pnginfo.h> // Not needed directly but otherwise the error
					 // "C4150: deletion of pointer to incomplete type"
					 // will show up.


using namespace std;

namespace AvoidTheBug3D {


/// Image loading class. Only handles RGB encoded data in PNG files for now.
class Image {
private:
	// Configuration & logging objects
	boost::shared_ptr<Configuration> cfg;
	boost::shared_ptr<GameLog> log;

	png_infop pngInformation;
	png_structp pngStructure;

	int width, height;
	png_byte colorType;
	png_byte bitDepth;
	int numberOfPasses;

	png_bytep* rowPointers;

	unsigned short* imageData;

	// Load image from a .png file
	void loadFromFile(string fileLocation);

public:
	/**
	 * Constructor
	 * @param fileLocation Location of image file
	 * @param cfg Game configuration object
	 * @param log Game log
	 */
	Image(string fileLocation, const boost::shared_ptr<Configuration> &cfg,
			const boost::shared_ptr<GameLog> &log);

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
	unsigned short* getData() const;

};

}
#endif /* IMAGE_H_ */
