/*
* GameLogic.cpp
*
*  Created on: Dec 26, 2013
*      Author: Dimitri Kourkoulis
*/

#include "GameLogic.h"
#include <glm/glm.hpp>

namespace AvoidTheBug3D {

	GameLogic::GameLogic(const boost::shared_ptr<Configuration> cfg,
		const boost::shared_ptr<GameLog> log) {

			this->cfg = cfg;
			this->log = log;

			goat = boost::shared_ptr<WorldObject> (
				new WorldObject("animal",
				"/Game/Data/Goat/goatAnim",
				cfg, log, "/Game/Data/Goat/Goat.png", 19));
			goat->setOffset(-1.2f, -1.0f, -4.0f);
			
			scene = boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > >(
				new vector<boost::shared_ptr<WorldObject> >());
			scene->push_back(goat);

			rotation = 0.0f;
	}

	GameLogic::~GameLogic() {
		// TODO Auto-generated destructor stub
	}

	void GameLogic::process( const KeyInput &keyInput )
	{
		const boost::shared_ptr<glm::vec3> goatRotation = goat->getRotation();

		goat->startAnimating();
		if(keyInput.left) {
			goatRotation->y += 0.03f;

			if (goatRotation->y > 6.28f)
				goatRotation->y = 0.0f;
			
		}
		else if (keyInput.right) {
			goatRotation->y -= 0.03f;

			if (goatRotation->y < -6.28f)
				goatRotation->y = 0.0f;
		}
		else
		{
			goat->stopAnimating();
		}
		
		goat->animate();
		goat->setRotation(rotation, goatRotation->y, rotation);
	}

} /* namespace AvoidTheBug3D */
