/*
 * WorldObject.cpp
 *
 *  Created on: Dec 26, 2013
 *      Author: Dimitri Kourkoulis
 */

#include "WorldObject.h"

namespace AvoidTheBug3D {

void WorldObject::initPropVectors() {
    this->colour = boost::shared_ptr<glm::vec3>(new glm::vec3(0, 0 ,0));
    this->location = boost::shared_ptr<glm::vec3>(new glm::vec3(0, 0 ,0));
    this->orientation = boost::shared_ptr<glm::vec3>(new glm::vec3(0, 0 ,0));
}

WorldObject::WorldObject(string name, string modelPath,
        boost::shared_ptr<Configuration> cfg,
		boost::shared_ptr<GameLog> log) {
	this->name = name;
	this->log = log;
	this->model = boost::shared_ptr<Model>(
			new Model(modelPath, cfg, log));
    this->initPropVectors();

}

WorldObject::WorldObject(string name, string modelPath, string texturePath,
		boost::shared_ptr<Configuration> cfg, boost::shared_ptr<GameLog> log) {
	this->name = name;
	this->log = log;
	this->model = boost::shared_ptr<Model>(
			new Model(modelPath, cfg, log));
	this->texture = boost::shared_ptr<Image>(
			new Image(texturePath, cfg, log));
    this->initPropVectors();
}

WorldObject::~WorldObject() {

}

const boost::shared_ptr<Model>& WorldObject::getModel() const {
	return model;
}

const boost::shared_ptr<Image>& WorldObject::getTexture() const {
	return texture;
}

const string WorldObject::getName()
{
	return name;
}

const boost::shared_ptr<glm::vec3>& WorldObject::getColour() {
    return colour;
}

void WorldObject::setColour(const float &r, const float &g, const float &b) {
    colour = boost::shared_ptr<glm::vec3>(new glm::vec3(r, g ,b));
}

const boost::shared_ptr<glm::vec3>& WorldObject::getLocation() const {
	return location;
}

void WorldObject::setLocation(const float &x, const float &y, const float &z) {
	location = boost::shared_ptr<glm::vec3>(new glm::vec3(x, y ,z));
}

const boost::shared_ptr<glm::vec3>& WorldObject::getOrientation() const {
	return orientation;
}

void WorldObject::setOrientation(const float &x, const float &y,
		const float &z) {
	orientation = boost::shared_ptr<glm::vec3>(new glm::vec3(x, y ,z));
}

}

