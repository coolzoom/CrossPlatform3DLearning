/*
* GameLogic.cpp
*
*  Created on: Dec 26, 2013
*      Author: Dimitri Kourkoulis
*/

#define BUG_ROTATION_SPEED 0.09f
#define BUG_TURNING_ANGLE 0.08f
#define BUG_SPEED 0.06f

#define GOAT_ROTATION_SPEED 0.03f
#define GOAT_SPEED 0.05f

#define FULL_ROTATION 6.28f // More or less 360 degrees in radians

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

	void GameLogic::moveGoat( const KeyInput &keyInput )
	{
		const boost::shared_ptr<glm::vec3> goatRotation = goat->getRotation();
		const boost::shared_ptr<glm::vec3> goatOffset = goat->getOffset();

		goat->stopAnimating();

		if(keyInput.left) {
			goatRotation->y -= GOAT_ROTATION_SPEED;

			if (goatRotation->y < - FULL_ROTATION)
				goatRotation->y = 0.0f;
			goat->startAnimating();

		}
		else if (keyInput.right) {
			goatRotation->y += GOAT_ROTATION_SPEED;

			if (goatRotation->y > FULL_ROTATION)
				goatRotation->y = 0.0f;
			goat->startAnimating();
		}

		if(keyInput.up) {
			float a = 

				goatOffset->x -= glm::cos(goatRotation->y) * GOAT_SPEED;
			goatOffset->z -= glm::sin(goatRotation->y) * GOAT_SPEED;

			goat->startAnimating();

		}
		else if (keyInput.down) {
			goatOffset->x += glm::cos(goatRotation->y) * GOAT_SPEED;
			goatOffset->z += glm::sin(goatRotation->y) * GOAT_SPEED;

			goat->startAnimating();
		}

		goat->animate();
		
		goat->setRotation(0.0f, goatRotation->y, 0.0f);

	}

	void GameLogic::moveBug()
	{
		const boost::shared_ptr<glm::vec3> bugRotation = bug->getRotation();
		const boost::shared_ptr<glm::vec3> bugOffset = bug->getOffset();

		bugRotation->x = -BUG_TURNING_ANGLE;

		bugRotation->y -= BUG_ROTATION_SPEED;

		if (bugRotation->y < -FULL_ROTATION)
			bugRotation->y = 0.0f;

		bugOffset->x -= glm::cos(bugRotation->y) * BUG_SPEED;
		bugOffset->z -= glm::sin(bugRotation->y) * BUG_SPEED;

		bug->animate();
	}

	void GameLogic::process( const KeyInput &keyInput )
	{
		moveBug();
		moveGoat(keyInput);
	}

} /* namespace AvoidTheBug3D */
