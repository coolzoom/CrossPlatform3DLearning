#include "Renderer.h"
#include "GameException.h"
namespace AvoidTheBug3D {

Renderer::Renderer(boost::shared_ptr<Configuration> cfg,
		boost::shared_ptr<GameLog> log) {
	this->cfg = cfg;
	this->log = log;
	screen = 0;
	icon = SDL_LoadBMP("ONLINE32.BMP");

}

Renderer::~Renderer() {

}

void Renderer::Init(int width, int height) {
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
}

} // AvoidTheBug3D

