/*
 * WorldObject.cpp
 *
 *  Created on: Dec 26, 2013
 *      Author: Dimitri Kourkoulis
 */

#include "WorldObject.h"
#include <boost/assign.hpp>

namespace AvoidTheBug3D {

WorldObject::WorldObject(string name, string modelPath,
		boost::shared_ptr<Configuration> cfg, boost::shared_ptr<GameLog> log) {
	this->name = name;
	this->log = log;
	this->model = boost::shared_ptr<Model>(
			new Model(modelPath, false, true, cfg, log));

}

WorldObject::WorldObject(string name, string modelPath, string texturePath,
		boost::shared_ptr<Configuration> cfg, boost::shared_ptr<GameLog> log) {
	this->name = name;
	this->log = log;
	this->model = boost::shared_ptr<Model>(
			new Model(modelPath, false, true, cfg, log));
	this->texture = boost::shared_ptr<Image>(new Image(texturePath, cfg, log));
}

WorldObject::~WorldObject() {
	// TODO Auto-generated destructor stub
}

const vector<float>& WorldObject::getLocation() const {
	return location;
}

void WorldObject::setLocation(const float &x, const float &y, const float &z) {
	location = boost::assign::list_of(x)(y)(z);
}

const boost::shared_ptr<Model>& WorldObject::getModel() const {
	return model;
}

const vector<float>& WorldObject::getOrientation() const {
	return orientation;
}

void WorldObject::setOrientation(const float &x, const float &y,
		const float &z) {
	orientation = boost::assign::list_of(x)(y)(z);
}

const boost::shared_ptr<Image>& WorldObject::getTexture() const {
	return texture;
}

}

