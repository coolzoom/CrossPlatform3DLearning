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
	// function developed based on example at
	// http://zarb.org/~gc/html/libpng.html

	FILE *fp = fopen((cfg->getHomeDirectory() + fileLocation).c_str(), "rb");

	if (!fp) {
		throw GameException(
				"Could not open file " + cfg->getHomeDirectory()
						+ fileLocation);
	}

	unsigned char header[8]; // Using maximum size that can be checked

	fread(header, 1, 8, fp);

	if (png_sig_cmp(header, 0, 8)) {
		throw GameException(
				"File " + cfg->getHomeDirectory() + fileLocation
						+ " is not recognised as a PNG file.");
	}

	png_structp pngStructure = png_create_read_struct(PNG_LIBPNG_VER_STRING,
	NULL, NULL, NULL);

	if (!pngStructure) {
		delete pngStructure;
		fclose(fp);
		throw GameException("Could not create PNG read structure.");
	}

	png_infop pngInformation = png_create_info_struct(pngStructure);

	if (!pngInformation) {
		fclose(fp);
		throw GameException("Could not create PNG information structure.");
	}

	if (setjmp(png_jmpbuf(pngStructure))) {
		delete pngInformation;
		delete pngStructure;
		fclose(fp);
		throw GameException("Could not setjmp.");
	}

	png_init_io(pngStructure, fp);
	png_set_sig_bytes(pngStructure, 8);

	png_read_info(pngStructure, pngInformation);


	delete pngInformation;
	delete pngStructure;
	fclose(fp);
}

}
