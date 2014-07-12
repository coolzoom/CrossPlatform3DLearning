#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <cstdlib>
#include <iostream>

#include "GameLog.h"
#include "Renderer.h"
#include "RendererOpenGL14.h"
#include "RendererOpenGL33.h"
#include "GameException.h"
#include <boost/smart_ptr.hpp>

using namespace std;
using namespace AvoidTheBug3D;

const GLuint frameRate = 60;

int main(int argc, char** argv) {

	GameLog *logPtr = new GameLog(cout);
	boost::shared_ptr<GameLog> log(logPtr);

	try {

		boost::shared_ptr<Configuration> cfg(new Configuration(log));

		//OpenGL v1.4 or v3.3. Uncomment accordingly. Modify in combination with
		// WorldObject constructor (indexed drawing, multicolour params to Model)
		//boost::shared_ptr<Renderer> renderer(new RendererOpenGL14(cfg, log));
		boost::shared_ptr<Renderer> renderer(new RendererOpenGL33(cfg, log));

		renderer->Init(1024, 768);

		// program main loop
		bool done = false;

		// ticks for setting the frame rate
		GLuint ticks = SDL_GetTicks();
		GLuint prevTicks = ticks;
		GLuint ticksInterval = 1000 / frameRate;


		boost::shared_ptr<WorldObject> object = boost::shared_ptr<WorldObject>(new WorldObject("animal",
				"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTexture.obj",
				"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTexture.png", cfg, log));

		boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > scene(new vector<boost::shared_ptr<WorldObject> >());
		scene->push_back(object);

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
