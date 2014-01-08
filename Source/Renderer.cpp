/*
 * Renderer.cpp
 *
 *  Created on: Dec 26, 2013
 *      Author: Dimitri Kourkoulis
 */
#include "Renderer.h"
#include "GameException.h"
#include "GameLog.h"



namespace AvoidTheBug3D {

#include <GL/glew.h>
#include <SDL.h>

// The following need to be included AFTER glew.h
#include <GL/gl.h>
#include <GL/glu.h>

Renderer::Renderer(GameLog *log) {
	this->log = log;
	screen = 0;
	icon = SDL_LoadBMP("ONLINE32.BMP");

	angle = 0;
}

Renderer::~Renderer() {
	SDL_FreeSurface(icon);
	SDL_FreeSurface(screen);
	SDL_Quit();

}

void Renderer::Init(int width, int height) {

	// initialize SDL video
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		LOGERROR(SDL_GetError());
		throw GameException(string("Unable to init SDL"));
	}

	glewInit();

	if (glewIsSupported("GL_VERSION_2_1"))
		LOGINFO("Ready for OpenGL 2.1");
	else {
		LOGINFO("OpenGL 2.1 is not supported by HW but maybe by SW");
		// Even if not supported by hardware, it may be
		// supported by software. In Linux, try
		// LIBGL_ALWAYS_SOFTWARE=1 glxinfo | grep -i Opengl
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

	//LOGINFO("OpenGL version supported by machine:");
	//LOGINFO(string(glGetString(GL_VERSION)).c_str());

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

void Renderer::DrawScene() {
	if (angle > 360)
		angle = 0;
	angle += 3;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -7.0f);

	glRotatef(angle, 1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);				// start drawing a polygon (4 sided)

	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);		// Normal Pointing Towards Viewer
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);	// Point 1 (Front)
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);	// Point 2 (Front)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);	// Point 3 (Front)
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);	// Point 4 (Front)
	// Back Face
	glNormal3f(0.0f, 0.0f, -1.0f);			// Normal Pointing Away From Viewer
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Back)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);	// Point 2 (Back)
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);	// Point 3 (Back)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);	// Point 4 (Back)
	// Top Face
	glNormal3f(0.0f, 1.0f, 0.0f);					// Normal Pointing Up
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);	// Point 1 (Top)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);	// Point 2 (Top)
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);	// Point 3 (Top)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);	// Point 4 (Top)
	// Bottom Face
	glNormal3f(0.0f, -1.0f, 0.0f);					// Normal Pointing Down
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Bottom)
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);	// Point 2 (Bottom)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);	// Point 3 (Bottom)
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);	// Point 4 (Bottom)
	// Right face
	glNormal3f(1.0f, 0.0f, 0.0f);					// Normal Pointing Right
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);	// Point 1 (Right)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);	// Point 2 (Right)
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);	// Point 3 (Right)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);	// Point 4 (Right)
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Left)
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);	// Point 2 (Left)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);	// Point 3 (Left)
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);	// Point 4 (Left)

	glEnd();					// done with the polygon

	// swap buffers to display, since we're double buffered.
	SDL_GL_SwapBuffers();
}
} /* namespace AvoidTheBug3D */
