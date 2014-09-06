/*
 * WorldObject.cpp
 *
 *  Created on: Dec 26, 2013
 *      Author: Dimitri Kourkoulis
 */

#include "WorldObject.h"

namespace AvoidTheBug3D {

void WorldObject::initPropVectors() {
    this->colour = boost::shared_ptr<glm::vec4>(new glm::vec4(0, 0 ,0, 0));
    this->offset = boost::shared_ptr<glm::vec3>(new glm::vec3(0, 0 ,0));
    this->rotation = boost::shared_ptr<glm::vec3>(new glm::vec3(0, 0 ,0));
}

WorldObject::WorldObject(const string &name, const string &modelPath,
        const boost::shared_ptr<Configuration> cfg,
		const boost::shared_ptr<GameLog> log) {
	this->name = name;
	this->log = log;
	this->model = boost::shared_ptr<Model>(
			new Model(modelPath, cfg, log));
    this->initPropVectors();

}

WorldObject::WorldObject(const string &name, const string &modelPath, const string &texturePath,
		const boost::shared_ptr<Configuration> cfg, const boost::shared_ptr<GameLog> log) {
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

const boost::shared_ptr<glm::vec4>& WorldObject::getColour() {
    return colour;
}

void WorldObject::setColour(const float &r, const float &g, const float &b, const float &a) {
    colour = boost::shared_ptr<glm::vec4>(new glm::vec4(r, g ,b, a));
}

const boost::shared_ptr<glm::vec3>& WorldObject::getOffset() const {
	return offset;
}

void WorldObject::setOffset(const float &x, const float &y, const float &z) {
	offset = boost::shared_ptr<glm::vec3>(new glm::vec3(x, y ,z));
}

const boost::shared_ptr<glm::vec3>& WorldObject::getRotation() const {
	return rotation;
}

void WorldObject::setRotation(const float &x, const float &y,
		const float &z) {
	rotation = boost::shared_ptr<glm::vec3>(new glm::vec3(x, y ,z));
}

}

