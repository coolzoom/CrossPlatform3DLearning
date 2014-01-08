/*
 * Renderer.h
 *
 *  Created on: Dec 26, 2013
 *      Author: Dimitri Kourkoulis
 */

#include <GL/glew.h>
#include <SDL.h>

// The following need to be included AFTER glew.h
#include <GL/gl.h>
#include <GL/glu.h>

#ifndef RENDERER_H_
#define RENDERER_H_

#include "GameLog.h"



namespace AvoidTheBug3D {

const GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
const GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat LightPosition[] = { -5.0f, 0.0f, 2.0f, 1.0f };


/**
 * Rendering class
 */
class Renderer {
private:
	GameLog *log;
	float angle;

	SDL_Surface *screen;
	SDL_Surface *icon;

	GLuint texture[3];

public:
	/**
	 * Default constructor
	 * @param log The logger class to be used
	 */
	Renderer(GameLog *log);

	/**
	 * Initialise renderer (OpenGL, GLEW, etc)
	 * @param width The width of the window
	 * @param height The height of the window
	 */
	void Init(int width, int height);

	void DrawScene();

	/**
	 * Destructor
	 */
	virtual ~Renderer();
};

} /* namespace AvoidTheBug3D */

#endif /* RENDERER_H_ */
