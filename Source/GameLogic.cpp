/*
* GameLogic.cpp
*
*  Created on: Dec 26, 2013
*      Author: Dimitri Kourkoulis
*/

#define MAX_Z -2.0f
#define MIN_Z -24.0f

#define GROUND_Y -1.0f

#define BUG_ROTATION_SPEED 0.12f
#define BUG_DIVE_TILT 0.8f
#define BUG_SPEED 0.08f
#define BUG_DIVE_DURATION 30
#define BUG_START_DIVE_DISTANCE 0.1f
#define BUG_FLIGHT_HEIGHT 1.4f

#define GOAT_ROTATION_SPEED 0.1f
#define GOAT_SPEED 0.05f

#define ROUND_2_DECIMAL(x) (floorf(100 * x + 0.5) / 100)

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
			goat->setOffset(-1.2f, GROUND_Y, -4.0f);

			bug = boost::shared_ptr<WorldObject> (
				new WorldObject("bug",
				"/Game/Data/Bug/bugAnim",
				cfg, log, 9));
			bug->setOffset(0.5f, GROUND_Y + BUG_FLIGHT_HEIGHT, -18.0f);
			bug->setColour(0.2f, 0.2f, 0.2f, 1.0f);
			// The bug will always be flapping its wings, so we might as well set
			// it to do so here
			bug->setFrameDelay(2);
			bug->startAnimating();

			bugVerticalSpeed = ROUND_2_DECIMAL(BUG_FLIGHT_HEIGHT / BUG_DIVE_DURATION);

			scene = boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > >(
				new vector<boost::shared_ptr<WorldObject> >());
			scene->push_back(goat);
			scene->push_back(bug);

			bugState = FLYING_STRAIGHT;
			bugPreviousState = FLYING_STRAIGHT;
			bugFramesInCurrentState = 1;
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

			if (goatOffset->z < MIN_Z)
				goatOffset->z = MIN_Z;
			if (goatOffset->z > MAX_Z) 
				goatOffset->z = MAX_Z;

			if (goatOffset->x < goatOffset-> z)
				goatOffset->x = goatOffset-> z;
			if (goatOffset->x > -(goatOffset->z)) 
				goatOffset->x = -(goatOffset->z);

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

		float xDistance = bug->getOffset()->x - goat->getOffset()->x;
		float yDistance = bug->getOffset()->z - goat->getOffset()->z;
		float distance = ROUND_2_DECIMAL(glm::sqrt(glm::pow<float>(xDistance, 2 ) + glm::pow<float>(yDistance, 2 )));

		glm::vec2 goatRelPos(ROUND_2_DECIMAL(xDistance / distance), ROUND_2_DECIMAL(yDistance / distance));

		glm::vec2 bugDirection(glm::cos(bug->getRotation()->y), glm::sin(bug->getRotation()->y));

		float dotPosDir = glm::dot<float>(goatRelPos, bugDirection);

		// Bug state: decide
		if (bugState == bugPreviousState) {
			++bugFramesInCurrentState;
		}
		else
		{
			bugFramesInCurrentState = 1;
		}

		bugPreviousState = bugState;

		if (bugState == DIVING_DOWN)
		{
			if (bugFramesInCurrentState > BUG_DIVE_DURATION / 2)
			{
				bugState = DIVING_UP;
			}
		}
		else if (bugState == DIVING_UP)
		{
			if (bugFramesInCurrentState > BUG_DIVE_DURATION / 2) {
				bugState = FLYING_STRAIGHT;
				bugOffset->y = GROUND_Y + BUG_FLIGHT_HEIGHT; // Correction of possible rounding errors
			}
		}
		else
		{

			if (dotPosDir < 0.98f) 
			{
				if (glm::abs(xDistance) > BUG_START_DIVE_DISTANCE)
				{
					bugState = TURNING;
				}
				else
				{
					bugState = FLYING_STRAIGHT;
				}

			}
			else {
				bugState = DIVING_DOWN;
			}

		}

		// Bug state: represent

		bugRotation->z = 0;

		if (bugState == TURNING)
		{

			bugRotation->y -= BUG_ROTATION_SPEED;

		}
		else if (bugState == DIVING_DOWN)
		{
			bugRotation->z = -BUG_DIVE_TILT;
			bugOffset->y -= bugVerticalSpeed;
		}
		else if (bugState == DIVING_UP)
		{
			bugRotation->z = BUG_DIVE_TILT;
			bugOffset->y += bugVerticalSpeed;
		}



		if (bugRotation->y < -FULL_ROTATION)
			bugRotation->y = 0.0f;


		bugOffset->x -= glm::cos(bugRotation->y) * BUG_SPEED;
		bugOffset->z -= glm::sin(bugRotation->y) * BUG_SPEED;

		if (bugOffset->z < MIN_Z)
			bugOffset->z = MIN_Z;
		if (bugOffset->z > MAX_Z) 
			bugOffset->z = MAX_Z;

		if (bugOffset->x < bugOffset-> z)
			bugOffset->x = bugOffset-> z;
		if (bugOffset->x > -(bugOffset->z)) 
			bugOffset->x = -(bugOffset->z);



		bug->animate();
	}

	void GameLogic::process( const KeyInput &keyInput )
	{
		moveBug();
		moveGoat(keyInput);
	}

} /* namespace AvoidTheBug3D */
