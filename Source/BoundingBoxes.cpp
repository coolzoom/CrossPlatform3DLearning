/*
* BoundingBoxes.cpp
*
*  Created on: Oct 10, 2014
*      Author: Dimitri Kourkoulis
*/

#include "BoundingBoxes.h"

namespace AvoidTheBug3D {

	/**
	* Constructor
	* 
	* @param	cfg	The configuration.
	* @param	log	The log.
	*/
	BoundingBoxes::BoundingBoxes(const boost::shared_ptr<Configuration> cfg, const boost::shared_ptr<GameLog> log) {
		this->cfg = cfg;
		this->log = log;
	}

	BoundingBoxes::~BoundingBoxes() {

	}
}