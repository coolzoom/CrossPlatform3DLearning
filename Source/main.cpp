#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <cstdlib>
#include <iostream>
#include "GameLog.h"
#include "GameException.h"
#include <boost/smart_ptr.hpp>
#include "PlayerView.h"

using namespace std;
using namespace AvoidTheBug3D;

const GLuint frameRate = 60;

int main(int argc, char** argv) {

	boost::shared_ptr<GameLog> log(new GameLog(cout));

	boost::shared_ptr<Configuration> cfg(new Configuration(log));

	try {
		boost::shared_ptr<PlayerView> pv(new PlayerView(cfg, log));

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
				pv->render();
			}
		}

	} catch (GameException &e) {
		LOGERROR(e.what());
		return 1;
	}

	return 0;
}
