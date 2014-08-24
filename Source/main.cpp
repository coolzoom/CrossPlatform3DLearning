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

	float rotation = 0.0f;

	boost::shared_ptr<GameLog> log(new GameLog(cout));

	boost::shared_ptr<Configuration> cfg(new Configuration(log));

	try {

		boost::shared_ptr<WorldObject> object1(
							new WorldObject("animal",
									"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTexture.obj",
									"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTextureRedBlackNumbers.png",
									 cfg, log));
        boost::shared_ptr<WorldObject> object(
							new WorldObject("animal",
									"/Game/Data/Cube/CubeNoTexture.obj",
									 cfg, log));
        object->setColour(1.0f, 1.0f, 0.0f);
		object->setOffset(1.5f, -1.0f, -8.0f);
		object1->setOffset(-1.2f, -1.0f, -4.0f);
        boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > scene(
				new vector<boost::shared_ptr<WorldObject> >());
		scene->push_back(object);
		scene->push_back(object1);

        boost::shared_ptr<Renderer> renderer(new Renderer(cfg, log));
		renderer->init(640, 480, true);

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

				if (rotation > 6.28)
					rotation = 0.0;
				rotation += 0.03f;

				object1->setRotation(rotation, rotation, rotation);
				object->setRotation(-rotation, rotation, rotation);

				renderer->drawScene(scene);
			}
		}

	} catch (GameException &e) {
		LOGERROR(e.what());
		return 1;
	}

	return 0;
}
