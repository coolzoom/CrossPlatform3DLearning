/*
 * Renderer.h
 *
 *  Created on: Jan 15, 2014
 *      Author: Dimitri Kourkoulis
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <boost/smart_ptr.hpp>
#include "WorldObject.h"
#include <vector>

namespace AvoidTheBug3D {

class Renderer {

public:

	/**
	 * Default constructor
	 */
	Renderer();

	/**
	 * Initialise renderer (OpenGL, GLEW, etc)
	 * @param width The width of the window
	 * @param height The height of the window
	 */
	virtual void Init(int width, int height) = 0;

	/**
	 * Draw the scene
	 */
	virtual void DrawScene(boost::shared_ptr<vector<WorldObject> > scene) = 0;

	/**
	 * Destructor
	 */
	virtual ~Renderer();

};

} /* namespace AvoidTheBug3D */

#endif /* RENDERER_H_ */
