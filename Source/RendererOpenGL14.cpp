/*
 * Renderer.cpp
 *
 *  Created on: Dec 26, 2013
 *      Author: Dimitri Kourkoulis
 */
#include "RendererOpenGL14.h"
#include "GameException.h"
#include "GameLog.h"
#include <boost/foreach.hpp>
#include <iterator>

namespace AvoidTheBug3D {

RendererOpenGL14::RendererOpenGL14(boost::shared_ptr<GameLog> log) {
	this->log = log;
	screen = 0;
	icon = SDL_LoadBMP("ONLINE32.BMP");
	angle = 0;
}

RendererOpenGL14::~RendererOpenGL14() {
	LOGINFO("OpenGL 1.4 renderer getting destroyed");
	SDL_FreeSurface(icon);
	SDL_FreeSurface(screen);
	SDL_Quit();
}

void RendererOpenGL14::Init(int width, int height) {

	// initialize SDL video
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		LOGERROR(SDL_GetError());
		throw GameException(string("Unable to init SDL"));
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_WM_SetCaption("SDL Application", "SDL Test");

	SDL_WM_SetIcon(icon, NULL);

	screen = SDL_SetVideoMode(1024, 768, 32, SDL_OPENGL); // *** SDL_HWSURFACE //DL_OPENGL |SDL_FULLSCREEN SDL_HWSURFACE SDL_DOUBLEBUF | );

	if (!screen) {

		LOGERROR(SDL_GetError());
		throw GameException("Unable to set video");
	}

	string glVersion = (char*) glGetString(GL_VERSION);
	glVersion = "OpenGL version supported by machine: " + glVersion;
	LOGINFO(glVersion);

	if (glewInit() != GLEW_OK) {
		throw GameException("Error initialising GLEW");
	}

	if (glewIsSupported("GL_VERSION_3_3")) {
		LOGINFO("Ready for OpenGL 3.3");
	} else {
		LOGINFO("OpenGL 3.3 is not supported");
	}

	glEnable(GL_TEXTURE_2D);

	glViewport(0, 0, width, height);
	glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);// This Will Clear The Background Color To Black
	glClearDepth(1.0f);				// Enables Clearing Of The Depth Buffer
	glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);				// The Type Of Depth Test To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// Really Nice Perspective Calculations

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);	// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	// Position The Light

	glEnable(GL_LIGHT1);							// Enable Light One
	glEnable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);	// Full Brightness, 50% Alpha ( NEW )
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);// Blending Function For Translucency Based On Source Alpha Value ( NEW )
	glEnable(GL_BLEND);		// Turn Blending On
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				// Reset The Projection Matrix

	gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);// Calculate The Aspect Ratio Of The Window

	glMatrixMode(GL_MODELVIEW);
}

void RendererOpenGL14::DrawScene(
		boost::shared_ptr<vector<WorldObject> > scene) {
	if (angle > 360)
		angle = 0;
	angle += 3;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -7.0f);

	glRotatef(angle, 1.0f, 1.0f, 0.0f);

	for (std::vector<WorldObject>::iterator it = scene->begin();
			it != scene->end(); it++) {

		glBegin(GL_QUADS);

		vector<float*>* vertices = it->getModel()->getVertices();


		for (std::vector<float*>::iterator vit = vertices->begin();
				vit != vertices->end(); vit++) {
			glVertex3f(*vit[0], *vit[1], *vit[2]);
		}

		glEnd();
	}

	// swap buffers to display, since we're double buffered.
	SDL_GL_SwapBuffers();

}
} /* namespace AvoidTheBug3D */
