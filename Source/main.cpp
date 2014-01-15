#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <cstdlib>
#include <iostream>

#include "GameLog.h"
#include "Renderer.h"
#include "RendererOpenGL14.h"
#include "GameException.h"

using namespace std;
using namespace AvoidTheBug3D;

const GLuint frameRate = 60;

int main(int argc, char** argv) {

	GameLog *log;

	log = new GameLog(cout);

	Renderer *renderer = new RendererOpenGL14(log);
	try
	{
		renderer->Init(1024, 768);
	}
	catch(GameException &e)
	{
		delete renderer;
		LOGERROR(e.what());
		return 1;
	}

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
			renderer->DrawScene();
		}
	}
	delete renderer;
	delete log;
	return 0;
}
