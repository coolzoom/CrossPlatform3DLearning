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
	}

	GameLogic::~GameLogic() {
		// TODO Auto-generated destructor stub
	}

	void GameLogic::process( const KeyInput &keyInput )
	{
		const boost::shared_ptr<glm::vec3> goatRotation = goat->getRotation();
		const boost::shared_ptr<glm::vec3> goatOffset = goat->getOffset();
		float goatSpeed = 0.05f;

		goat->stopAnimating();

		if(keyInput.left) {
			goatRotation->y -= 0.03f;

			if (goatRotation->y > 6.28f)
				goatRotation->y = 0.0f;
			goat->startAnimating();
			
		}
		else if (keyInput.right) {
			goatRotation->y += 0.03f;
			
			if (goatRotation->y < -6.28f)
				goatRotation->y = 0.0f;
			goat->startAnimating();
		}
		
		if(keyInput.up) {
			float a = 

			goatOffset->x -= glm::cos(goatRotation->y) * goatSpeed;
			goatOffset->z -= glm::sin(goatRotation->y) * goatSpeed;

			goat->startAnimating();

		}
		else if (keyInput.down) {
			goatOffset->x += glm::cos(goatRotation->y) * goatSpeed;
			goatOffset->z += glm::sin(goatRotation->y) * goatSpeed;

			goat->startAnimating();
		}
		
		goat->animate();
		goat->setRotation(0.0f, goatRotation->y, 0.0f);
	}

} /* namespace AvoidTheBug3D */
