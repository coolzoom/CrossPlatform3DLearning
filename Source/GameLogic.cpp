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
				new WorldObject("goat",
				"/Game/Data/Goat/goatAnim",
				cfg, log, 19, "/Game/Data/Goat/Goat.png"));
			goat->setOffset(-1.2f, -1.0f, -4.0f);

			bug = boost::shared_ptr<WorldObject> (
				new WorldObject("bug",
				"/Game/Data/Bug/bugAnim",
				cfg, log, 9));
			bug->setOffset(0.5f, 0.4f, -4.0f);
			bug->setColour(0.2f, 0.2f, 0.2f, 1.0f);
			// The bug will always be flapping its wings, so we might as well set
			// it to do so here
			bug->startAnimating();

			scene = boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > >(
				new vector<boost::shared_ptr<WorldObject> >());
			scene->push_back(goat);
			scene->push_back(bug);

			bugState = FLYING_STRAIGHT;	
	}

	GameLogic::~GameLogic() {
		// TODO Auto-generated destructor stub
	}

	void GameLogic::process( const KeyInput &keyInput )
	{
		const boost::shared_ptr<glm::vec3> goatRotation = goat->getRotation();
		const boost::shared_ptr<glm::vec3> goatOffset = goat->getOffset();
		float goatSpeed = 0.05f;
		
		const boost::shared_ptr<glm::vec3> bugRotation = bug->getRotation();
		const boost::shared_ptr<glm::vec3> bugOffset = bug->getOffset();
		float bugSpeed = 0.06f;
		bugRotation->x = -0.8f;


		bugRotation->y -= 0.09f;

		if (bugRotation->y < -6.28f)
			bugRotation->y = 0.0f;

		bugOffset->x -= glm::cos(bugRotation->y) * bugSpeed;
		bugOffset->z -= glm::sin(bugRotation->y) * bugSpeed;

		goat->stopAnimating();

		if(keyInput.left) {
			goatRotation->y -= 0.03f;

			if (goatRotation->y < - 6.28f)
				goatRotation->y = 0.0f;
			goat->startAnimating();
			
		}
		else if (keyInput.right) {
			goatRotation->y += 0.03f;
			
			if (goatRotation->y > 6.28f)
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
		bug->animate();
		goat->setRotation(0.0f, goatRotation->y, 0.0f);
	}

} /* namespace AvoidTheBug3D */
