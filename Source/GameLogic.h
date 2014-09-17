/*
* GameLogic.h
*
*  Created on: Dec 26, 2013
*      Author: Dimitri Kourkoulis
*/

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include <boost/smart_ptr.hpp>
#include "Configuration.h"
#include "GameLog.h"

namespace AvoidTheBug3D {

	class GameLogic {

	private:

		boost::shared_ptr<Configuration> cfg;
		boost::shared_ptr<GameLog> log;

	public:

		/**
		* Constructor
		* @param cfg The game's configuration object
		* @param log The game's logging object
		*/
		GameLogic(const boost::shared_ptr<Configuration> cfg,
			const boost::shared_ptr<GameLog> log);

		/**
		* Destructor
		*/
		~GameLogic();
	};

} /* namespace AvoidTheBug3D */

#endif /* GAMELOGIC_H_ */
