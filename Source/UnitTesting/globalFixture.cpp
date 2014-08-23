/*
* globalFixture.cpp
*
*  Created on: Aug 10, 2014
*      Author: Dimitri Kourkoulis
*/
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "globals.h"

#include "../Renderer.h"
#include "../GameException.h"

#include "../WorldObject.h"

using namespace AvoidTheBug3D;
using namespace std;

Globals *globals;

// Setup / Teardown
struct GlobalSetupTeardown
{

    GlobalSetupTeardown()
    {

        globals = new Globals();

        globals->log = boost::shared_ptr<GameLog>(new GameLog(cout));
        boost::shared_ptr<GameLog> log = globals->log;

        globals->cfg = boost::shared_ptr<Configuration>(new Configuration(log));
        boost::shared_ptr<Configuration> cfg = globals->cfg;



        boost::shared_ptr<WorldObject> object(
            new WorldObject("animal",
                            "/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTexture.obj",
                            "/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTextureRedBlackNumbers.png",
                            cfg, log));
        boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > scene(
            new vector<boost::shared_ptr<WorldObject> >());
        scene->push_back(object);

        boost::shared_ptr<Renderer> renderer(new Renderer(cfg, log));
        renderer->init(640, 480, false);

    }

    ~GlobalSetupTeardown()
    {
        delete globals;
    }
};

BOOST_GLOBAL_FIXTURE( GlobalSetupTeardown );

