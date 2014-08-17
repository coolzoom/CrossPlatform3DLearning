#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <cstdlib>
#include <iostream>

#ifndef SDLANDOPENGL
#define SDLANDOPENGL
//#define GLEW_STATIC
#define NO_SDL_GLEXT
// It seems that, when using glew,
// we do not need to include gl.h,
// glext.h or glu.h (if we do include
// them, they need to be included after
// glew.
#include "GL/glew.h"
#include "SDL_opengl.h"
#include "SDL.h"
#endif //SDLANDOPENGL

#include "GameLog.h"
#include "Renderer.h"
#include "RendererOpenGL21.h"
#include "RendererOpenGL33.h"
#include "GameException.h"
#include <boost/smart_ptr.hpp>
#include "WorldObject.h"

using namespace std;
using namespace AvoidTheBug3D;

const GLuint frameRate = 60;

SDL_Surface *screen;
SDL_Surface *icon;

int main(int argc, char** argv) {

	GameLog *logPtr = new GameLog(cout);
	boost::shared_ptr<GameLog> log(logPtr);

	boost::shared_ptr<Configuration> cfg(new Configuration(log));

	try {

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
									"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTextureRedBlackNumbers.png",
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

		} else {
			throw GameException(
					"None of the supported OpenGL versions (3.3 nor 2.1) are available.");
		}

		renderer->Init(1024, 768);

		boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > scene(
				new vector<boost::shared_ptr<WorldObject> >());
		scene->push_back(object);

		// program main loop
		bool done = false;

		// ticks for setting the frame rate
		GLuint ticks = SDL_GetTicks();
		GLuint prevTicks = ticks;
		GLuint ticksInterval = 1000 / frameRate;

		while (!done) {

			SDL_Event event;
			if (SDL_PollEvent(&event)) {
				switch (event.type) {

				case SDL_QUIT:
					done = true;
					break;

				case SDL_KEYDOWN: {
					if (event.key.keysym.sym == SDLK_ESCAPE)
						done = true;
					break;
				}
				}
			}

			ticks = SDL_GetTicks();
			if (ticks - prevTicks > ticksInterval) {
				prevTicks = ticks;
				renderer->DrawScene(scene);
			}
		}

	} catch (GameException &e) {
		LOGERROR(e.what());
		SDL_FreeSurface(icon);
		SDL_FreeSurface(screen);
		SDL_Quit();
		return 1;
	}

	SDL_FreeSurface(icon);
	SDL_FreeSurface(screen);
	SDL_Quit();

	return 0;
}
