/*
* globalFixture.cpp
*
*  Created on: Aug 10, 2014
*      Author: Dimitri Kourkoulis
*/
#include <boost/test/unit_test.hpp>
#include <iostream>

#ifndef SDLANDOPENGL
#define SDLANDOPENGL
#define NO_SDL_GLEXT
#include "GL/glew.h"
#include "SDL_opengl.h"
#include "SDL.h"
#endif //SDLANDOPENGL

#include "../GameLog.h"
#include "../Renderer.h"
#include "../RendererOpenGL21.h"
#include "../RendererOpenGL33.h"
#include "../GameException.h"
#include <boost/smart_ptr.hpp>
#include "../WorldObject.h"

using namespace AvoidTheBug3D;
using namespace std;

// Setup / Teardown
struct GlobalSetupTeardown
{
	SDL_Surface *screen;
	SDL_Surface *icon;

	GlobalSetupTeardown() {

		GameLog *logPtr = new GameLog(cout);
		boost::shared_ptr<GameLog> log(logPtr);

		boost::shared_ptr<Configuration> cfg(new Configuration(log));

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

		icon = SDL_LoadBMP("ONLINE32.BMP");
		SDL_WM_SetIcon(icon, NULL);
		screen = SDL_SetVideoMode(1024, 768, 32, SDL_OPENGL); // *** SDL_HWSURFACE //DL_OPENGL |SDL_FULLSCREEN SDL_HWSURFACE SDL_DOUBLEBUF | );

		if (!screen) {

			LOGERROR(SDL_GetError());
			throw GameException("Unable to set video");
		}

		if (glewInit() != GLEW_OK) {
			throw GameException("Error initialising GLEW");
		} else {
			string glewVersion = (char*) glewGetString(GLEW_VERSION);
			LOGINFO("Using GLEW version " + glewVersion);
		}

		string glVersion = (char*) glGetString(GL_VERSION);
		glVersion = "OpenGL version supported by machine: " + glVersion;
		LOGINFO(glVersion);

		boost::shared_ptr<Renderer> renderer;
		boost::shared_ptr<WorldObject> object;
		if (glewIsSupported("GL_VERSION_3_3")) {
			LOGINFO("Ready for OpenGL 3.3");
			renderer = boost::shared_ptr<Renderer>(
				new RendererOpenGL33(cfg, log));

			object =
				boost::shared_ptr<WorldObject>(
				new WorldObject("animal",
				"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTexture.obj",
				"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTextureWhite.png",
				false, true, cfg, log));

		} else if (glewIsSupported("GL_VERSION_2_1")) {
			LOGINFO("Ready for OpenGL 2.1");
			renderer = boost::shared_ptr<Renderer>(
				new RendererOpenGL21(cfg, log));
			object =
				boost::shared_ptr<WorldObject>(
				new WorldObject("animal",
				"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimal.obj",
				false, false, cfg, log));

		}
	}

	~GlobalSetupTeardown() {
		SDL_FreeSurface(icon);
		SDL_FreeSurface(screen);
		SDL_Quit();
	}
};

BOOST_GLOBAL_FIXTURE( GlobalSetupTeardown );

