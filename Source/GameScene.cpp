/*
* GameScene.cpp
*
*  Created on: Oct 10, 2014
*      Author: Dimitri Kourkoulis
*/

#include "GameScene.h"

namespace AvoidTheBug3D {
	
	GameScene::GameScene(const boost::shared_ptr<Configuration> cfg,
		const boost::shared_ptr<GameLog> log){
			this->cfg = cfg;
			this->log = log;

			showingStartScreen = true;

			worldObjects = boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > >(
				new vector<boost::shared_ptr<WorldObject> >());
	}
	
	GameScene::~GameScene() {

	}
}