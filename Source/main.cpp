#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <cstdlib>
#include <iostream>

#include "GameLog.h"
#include "Renderer.h"
#include "GameException.h"
#include <boost/smart_ptr.hpp>
#include "WorldObject.h"

using namespace std;
using namespace AvoidTheBug3D;

const GLuint frameRate = 60;



int main(int argc, char** argv) {

	boost::shared_ptr<GameLog> log(new GameLog(cout));

	boost::shared_ptr<Configuration> cfg(new Configuration(log));

	try {

		boost::shared_ptr<WorldObject> object(
							new WorldObject("animal",
									"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTexture.obj",
									"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTextureRedBlackNumbers.png",
									false, true, cfg, log));
        boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > scene(
				new vector<boost::shared_ptr<WorldObject> >());
		scene->push_back(object);

        boost::shared_ptr<Renderer> renderer(new Renderer(cfg, log));
		renderer->init(1024, 768);

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
				renderer->drawScene(scene);
			}
		}

	} catch (GameException &e) {
		LOGERROR(e.what());
		return 1;
	}

	return 0;
}
