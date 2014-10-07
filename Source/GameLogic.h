#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include <boost/smart_ptr.hpp>
#include "Configuration.h"
#include "GameLog.h"
#include "WorldObject.h"
#include "KeyInput.h"
#include "GameScene.h"

namespace AvoidTheBug3D {

	/**
	 * @class	GameLogic
	 *
	 * @brief	Game logic
	 *
	 * @author	Dimitri Kourkoulis
	 * @date	Dec 26, 2013
	 */

	class GameLogic {

	private:

		boost::shared_ptr<Configuration> cfg;
		boost::shared_ptr<GameLog> log;

		boost::shared_ptr<WorldObject> goat;
		boost::shared_ptr<WorldObject> bug;

		enum GameState {START_SCREEN, PLAYING};
		GameState gameState;

		enum BugState {FLYING_STRAIGHT, TURNING, DIVING_DOWN, DIVING_UP};
		BugState bugState, bugPreviousState;
		int bugFramesInCurrentState;
		float bugVerticalSpeed;

		void initGame();
		void processGame(const KeyInput &keyInput);
		void processStartScreen(const KeyInput &keyInput);

		void moveGoat(const KeyInput &keyInput);
		void moveBug();
		
	public:

		/**
		 * @brief	The game scene.
		 */
		boost::shared_ptr<GameScene> gameScene;

		/**
		 * Constructor
		 * @param	cfg	The game's configuration object.
		 * @param	log	The game's logging object.
		 */
		GameLogic(const boost::shared_ptr<Configuration> cfg,
			const boost::shared_ptr<GameLog> log);

		/**
		* Destructor
		*/
		~GameLogic();

		/**
		 * Process conditions and set up the next frame, also taking into consideration
		 * the input from the keyboard
		 * 
		 * @param	keyInput	The keyboard input
		 */
		void process(const KeyInput &keyInput);
	};

} /* namespace AvoidTheBug3D */

#endif /* GAMELOGIC_H_ */
