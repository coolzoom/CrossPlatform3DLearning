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
#include <cmath>
#include <iostream>
namespace AvoidTheBug3D {

RendererOpenGL14::RendererOpenGL14( boost::shared_ptr<Configuration> cfg,
		 boost::shared_ptr<GameLog> log) : Renderer(cfg, log) {

	angle = 0;
}

RendererOpenGL14::~RendererOpenGL14() {
	LOGINFO("OpenGL 1.4 renderer getting destroyed");

}

void RendererOpenGL14::Init(int width, int height) {
	Renderer::Init(width, height);

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
	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);	// Full Brightness, 0% Alpha ( NEW )
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);// Blending Function For Translucency Based On Source Alpha Value ( NEW )
	//glEnable(GL_BLEND);		// Turn Blending On
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				// Reset The Projection Matrix

	gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);// Calculate The Aspect Ratio Of The Window

	glMatrixMode(GL_MODELVIEW);
}

void RendererOpenGL14::DrawScene(
		boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > scene) {
	if (angle > 360)
		angle = 0;
	angle += 3;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -7.0f);

	glRotatef(angle, 1.0f, 1.0f, 0.0f);

	for (std::vector<boost::shared_ptr<WorldObject> >::iterator it = scene->begin();
			it != scene->end(); it++) {

		glBegin(GL_TRIANGLES);

		vector<float*>* vertices = it->get()->getModel()->getVertices();
		vector<int*>* faces = it->get()->getModel()->getFaces();

		int numFaces = faces->size();
		for (int idx = 0; idx != numFaces; ++idx) {

			// Calculate and push normal
			float a [3] = {
					vertices->at(faces->at(idx)[1] - 1)[0] - vertices->at(faces->at(idx)[0] - 1)[0],
					vertices->at(faces->at(idx)[1] - 1)[1] - vertices->at(faces->at(idx)[0] - 1)[1],
					vertices->at(faces->at(idx)[1] - 1)[2] - vertices->at(faces->at(idx)[0] - 1)[2] };

			float b [3] = {
					vertices->at(faces->at(idx)[2] - 1)[0] - vertices->at(faces->at(idx)[0] - 1)[0],
					vertices->at(faces->at(idx)[2] - 1)[1] - vertices->at(faces->at(idx)[0] - 1)[1],
					vertices->at(faces->at(idx)[2] - 1)[2] - vertices->at(faces->at(idx)[0] - 1)[2] };

			float n[3] = {
					a[1] * b[2] - a[2] * b[1],
					a[2] * b[0] - a[0] * b[2],
					a[0] * b[1] - a[1] * b[0] };

			float l = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);

			n[0] /= l;
			n[1] /= l;
			n[2] /= l;

			glNormal3f(n[0], n[1], n[2]);

			// Push triangle
			glVertex3f(vertices->at(faces->at(idx)[0] - 1)[0], vertices->at(faces->at(idx)[0] - 1)[1], vertices->at(faces->at(idx)[0] - 1)[2]);
			glVertex3f(vertices->at(faces->at(idx)[1] - 1)[0], vertices->at(faces->at(idx)[1] - 1)[1], vertices->at(faces->at(idx)[1] - 1)[2]);
			glVertex3f(vertices->at(faces->at(idx)[2] - 1)[0], vertices->at(faces->at(idx)[2] - 1)[1], vertices->at(faces->at(idx)[2] - 1)[2]);
		}

		glEnd();
	}

	// swap buffers to display, since we're double buffered.
	SDL_GL_SwapBuffers();

}
} /* namespace AvoidTheBug3D */
