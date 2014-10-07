#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <cstdlib>
#include <iostream>
#include "GameLog.h"
#include "GameException.h"
#include <boost/smart_ptr.hpp>
#include "GameLogic.h"
#include "PlayerView.h"
#include "KeyInput.h"

using namespace std;
using namespace AvoidTheBug3D;

const GLuint frameRate = 60;

int main(int argc, char** argv)
{

	KeyInput input;

    boost::shared_ptr<GameLog> log(new GameLog(cout));

    boost::shared_ptr<Configuration> cfg(new Configuration(log));

    try
    {

        boost::shared_ptr<GameLogic> gameLogic(new GameLogic(cfg, log));

        boost::shared_ptr<PlayerView> pv(new PlayerView(cfg, log));

        // program main loop
        bool done = false;

        // ticks for setting the frame rate
        GLuint ticks = SDL_GetTicks();
        GLuint prevTicks = ticks;
        GLuint ticksInterval = 1000 / frameRate;

        while (!done)
        {

            SDL_Event event;
            if (SDL_PollEvent(&event))
            {

				const Uint8 *keyState = SDL_GetKeyState(NULL);

				input.up = keyState[SDLK_UP] == 1;
				input.down = keyState[SDLK_DOWN] == 1;
				input.left = keyState[SDLK_LEFT] == 1;
				input.right = keyState[SDLK_RIGHT] == 1;
				input.enter = keyState[SDLK_RETURN] == 1;

                switch (event.type)
                {

                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
                }
            }

            ticks = SDL_GetTicks();
            if (ticks - prevTicks > ticksInterval)
            {
				gameLogic->process(input);
                prevTicks = ticks;
                pv->render(gameLogic->gameScene);
            }
        }

    }
    catch (GameException &e)
    {
        LOGERROR(e.what());
        return 1;
    }

    return 0;
}
