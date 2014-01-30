/*
 * RendererOpenGL33.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: Dimitri Kourkoulis
 */

#include "RendererOpenGL33.h"
#include <fstream>
#include "GameException.h"

namespace AvoidTheBug3D {

RendererOpenGL33::RendererOpenGL33(boost::shared_ptr<Configuration> cfg,
		boost::shared_ptr<GameLog> log) :
		Renderer(cfg, log) {
	screen = 0;
	icon = SDL_LoadBMP("ONLINE32.BMP");
	vertexShader = loadShaderFromFile("/Game/Shaders/testShader.vert");
	fragmentShader = loadShaderFromFile("/Game/Shaders/testShader.frag");
}

void RendererOpenGL33::Init(int width, int height) {

	// initialize SDL video
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		LOGERROR(SDL_GetError());
		throw GameException(string("Unable to initialise SDL"));
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_WM_SetCaption("SDL Application", "SDL Test");

	SDL_WM_SetIcon(icon, NULL);

	screen = SDL_SetVideoMode(1024, 768, 32, SDL_OPENGL);

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

}

void RendererOpenGL33::DrawScene(
		boost::shared_ptr<vector<WorldObject> > scene) {
}

RendererOpenGL33::~RendererOpenGL33() {

}

string RendererOpenGL33::loadShaderFromFile(string fileLocation) {
	string shaderSource = "";
	ifstream file((cfg->getHomeDirectory() + fileLocation).c_str());
	string line;
	if (file.is_open()) {
		while (getline(file, line)) {
			shaderSource += line + "\n";
		}
	}
	return shaderSource;
}

} /* namespace AvoidTheBug3D */

