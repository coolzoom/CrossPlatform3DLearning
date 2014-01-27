#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <cstdlib>
#include <iostream>

#define DEBUG
#include "GameLog.h"
#include "Renderer.h"
#include "RendererOpenGL14.h"
#include "GameException.h"
#include <boost/smart_ptr.hpp>

using namespace std;
using namespace AvoidTheBug3D;

const GLuint frameRate = 60;

int main(int argc, char** argv) {

	GameLog *logPtr = new GameLog(cout);
	boost::shared_ptr<GameLog> log(logPtr);

	try {

		Configuration *confPtr = new Configuration(log);
		boost::shared_ptr<Configuration> cfg(confPtr);

		Renderer *rendererPtr = new RendererOpenGL14(log);
		boost::shared_ptr<Renderer> renderer(rendererPtr);

		renderer->Init(1024, 768);

		// program main loop
		bool done = false;

		// ticks for setting the frame rate
		GLuint ticks = SDL_GetTicks();
		GLuint prevTicks = ticks;
		GLuint ticksInterval = 1000 / frameRate;

		WorldObject *object = new WorldObject("animal",
				"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimal.obj", cfg, log);
		vector<WorldObject> *scenePtr = new vector<WorldObject>();
		scenePtr->push_back(*object);

		boost::shared_ptr<vector<WorldObject> > scene(scenePtr);

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
		return 1;
	}

	return 0;
}
