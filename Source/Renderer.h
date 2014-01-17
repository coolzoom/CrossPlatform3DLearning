/*
 * Renderer.h
 *
 *  Created on: Jan 15, 2014
 *      Author: Dimitri Kourkoulis
 */

#ifndef RENDERER_H_
#define RENDERER_H_

namespace AvoidTheBug3D {

class Renderer {

public:

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
	virtual void DrawScene() = 0;

	/**
	 * Destructor
	 */
	virtual ~Renderer();

};

} /* namespace AvoidTheBug3D */

#endif /* RENDERER_H_ */
