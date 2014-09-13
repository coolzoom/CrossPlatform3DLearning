/*
 * WorldObject.cpp
 *
 *  Created on: Dec 26, 2013
 *      Author: Dimitri Kourkoulis
 */

#include "WorldObject.h"
#include <sstream>
#include <iomanip>

namespace AvoidTheBug3D {

void WorldObject::initPropVectors() {
    this->colour = boost::shared_ptr<glm::vec4>(new glm::vec4(0, 0 ,0, 0));
    this->offset = boost::shared_ptr<glm::vec3>(new glm::vec3(0, 0 ,0));
    this->rotation = boost::shared_ptr<glm::vec3>(new glm::vec3(0, 0 ,0));
}

WorldObject::WorldObject(const string &name, const string &modelPath,
		const boost::shared_ptr<Configuration> cfg, const boost::shared_ptr<GameLog> log, const string &texturePath,
		const int &numFrames) {
	this->name = name;
	this->log = log;
	animating = false;
	framesWaited = 0;
	frameDelay = 1;
	currentFrame = 0;
	this->numFrames = numFrames;

	model = boost::shared_ptr<Model[]>(
		new Model[numFrames], []( Model *p ) { delete[] p; });

	if (numFrames > 1) {
		LOGINFO("Loading animated model (this may take a while):");
		for (int idx = 0; idx < numFrames; ++idx) {
			stringstream lss;
			lss << "Frame " << idx + 1 << " of " << numFrames << "...";
			LOGINFO(lss.str());
			stringstream ss;
			ss << setfill('0') << setw(6) << idx + 1;
			string frameNum = ss.str();
			model[idx].init(modelPath + "_" + frameNum + ".obj", cfg, log);
		}
	}
	else
	{
		model[0].init(modelPath, cfg, log);
	}
	
	if (texturePath != "") {
	this->texture = boost::shared_ptr<Image>(
			new Image(texturePath, cfg, log));
	}
    this->initPropVectors();
}

WorldObject::~WorldObject() {

}

Model& WorldObject::getModel() const {
	return model[currentFrame];
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

void WorldObject::startAnimating()
{
	animating = true;
}

void WorldObject::stopAnimating()
{
	animating = false;
}

void WorldObject::resetAnimation()
{
	currentFrame = 0;
}

void WorldObject::setFrameDelay( const int &delay )
{
	this->frameDelay = delay;
}

void WorldObject::animate()
{
	if(animating) {
		++framesWaited;
		if (framesWaited == frameDelay) {
			framesWaited = 0;
			++currentFrame;
			if (currentFrame == numFrames) {
				currentFrame = 0;
			}
		}
	}
}

}

