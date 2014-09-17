/*
* GameLogic.cpp
*
*  Created on: Dec 26, 2013
*      Author: Dimitri Kourkoulis
*/

#include "GameLogic.h"

namespace AvoidTheBug3D {

	GameLogic::GameLogic(const boost::shared_ptr<Configuration> cfg,
		const boost::shared_ptr<GameLog> log) {

			this->cfg = cfg;
			this->log = log;
	}

	GameLogic::~GameLogic() {
		// TODO Auto-generated destructor stub
	}

} /* namespace AvoidTheBug3D */
