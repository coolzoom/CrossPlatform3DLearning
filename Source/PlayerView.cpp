/*
* PlayerView.cpp
*
*  Created on: Dec 26, 2013
*      Author: Dimitri Kourkoulis
*/

#include "PlayerView.h"
#include <boost/scoped_ptr.hpp>


namespace AvoidTheBug3D {

	PlayerView::PlayerView(const boost::shared_ptr<Configuration> cfg,
		const boost::shared_ptr<GameLog> log) {

			this->cfg = cfg;
			this->log = log;

			goat = boost::shared_ptr<WorldObject> (
				new WorldObject("animal",
				"/Game/Data/Goat/goatAnim",
				cfg, log, "/Game/Data/Goat/Goat.png", 19));
			goat->setOffset(-1.2f, -1.0f, -4.0f);
			goat->startAnimating();
			scene = boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > >(
				new vector<boost::shared_ptr<WorldObject> >());
			scene->push_back(goat);

			rotation = 0.0f;

			renderer = boost::shared_ptr<Renderer>(new Renderer(cfg, log));
			renderer->init(640, 480, false);

			boost::scoped_ptr<Image> groundTexture (
				new Image("/Game/Data/OtherTextures/grass.png", cfg, log));
			renderer->generateTexture("ground", groundTexture->getData(), groundTexture->getWidth(), groundTexture->getHeight());

			boost::scoped_ptr<Image> skyTexture (
				new Image("/Game/Data/OtherTextures/sky.png", cfg, log));
			renderer->generateTexture("sky", skyTexture->getData(), skyTexture->getWidth(), skyTexture->getHeight());

	}

	PlayerView::~PlayerView() {
		// TODO Auto-generated destructor stub
	}

	void PlayerView::render()
	{
		float groundVerts[16] =
		{
			1.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 1.0f
		};

		float skyVerts[16] =
		{
			1.0f, 1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f, 1.0f,
			-1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 1.0f
		};


		if (rotation > 6.28)
			rotation = 0.0;
		rotation += 0.03f;
		goat->animate();
		goat->setRotation(rotation, rotation, rotation);

		renderer->drawScene(scene);

		renderer->renderTexturedQuad(&groundVerts[0], "ground");
		renderer->renderTexturedQuad(&skyVerts[0], "sky");
		SDL_Color textColour = {50, 50, 50, 255};

		renderer->renderText("Hello", textColour, -1.0f, 0.8f, 0.0f, -0.1f);
		renderer->swapBuffers();

	}

} /* namespace AvoidTheBug3D */
