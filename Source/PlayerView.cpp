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

			renderer = boost::shared_ptr<Renderer>(new Renderer(cfg, log));
			renderer->init(854, 480, false);

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

	void PlayerView::render(boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > scene)
	{

		renderer->clearScreen();

		// Draw the background
		
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

		renderer->renderTexturedQuad(&groundVerts[0], "ground");
		renderer->renderTexturedQuad(&skyVerts[0], "sky");

		renderer->drawScene(scene);

		SDL_Color textColour = {255, 255, 0, 255};
		renderer->renderText("Now it's chasing me! HELP!", textColour, -1.0f, 1.0f, 1.0f, 0.5f);
		
		renderer->swapBuffers();
	}

} /* namespace AvoidTheBug3D */
