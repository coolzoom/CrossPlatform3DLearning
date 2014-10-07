#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include <boost/smart_ptr.hpp>
#include "Configuration.h"
#include "GameLog.h"
#include "WorldObject.h"

namespace AvoidTheBug3D {

	/**
	* @struct	GameScene
	*
	* @brief	The game scene
	*
	* @author	Dimitri Kourkoulis
	* @date	Oct 10, 2014
	*/

	struct GameScene
	{
	private:
		boost::shared_ptr<Configuration> cfg;
		boost::shared_ptr<GameLog> log;
	public:

		/**
		 * @brief	Showing start screen.
		 */
		bool showingStartScreen;

		/**
		 * The set of world objects, in their current state.
		 *
		 * @return	The world objects.
		 */
		boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > worldObjects;

		/**
		* Constructor
		* @param	cfg	The game's configuration object.
		* @param	log	The game's logging object.
		*/
		GameScene(const boost::shared_ptr<Configuration> cfg,
			const boost::shared_ptr<GameLog> log);

		/**
		* Destructor
		*/
		~GameScene();
	};

}

#endif /* GAMESCENE_H_ */