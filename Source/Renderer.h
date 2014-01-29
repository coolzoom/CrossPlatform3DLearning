/*
 * Renderer.h
 *
 *  Created on: Jan 15, 2014
 *      Author: Dimitri Kourkoulis
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <boost/smart_ptr.hpp>
#include "WorldObject.h"
#include <vector>
#include "Configuration.h"
#include "GameLog.h"
#include <boost/smart_ptr.hpp>

namespace AvoidTheBug3D {

class Renderer {

protected:
	boost::shared_ptr<Configuration> cfg;
	boost::shared_ptr<GameLog> log;

public:

	/**
	 * Constructor
	 * @param cfg The game's configuration object
	 * @param log The game's logging object
	 */
	Renderer(boost::shared_ptr<Configuration> cfg,
			 boost::shared_ptr<GameLog> log);

	/**
	 * Initialise renderer (OpenGL, GLEW, etc)
	 * @param width The width of the window
	 * @param height The height of the window
	 */
	virtual void Init(int width, int height) = 0;

	/**
	 * Draw the scene
	 */
	virtual void DrawScene(boost::shared_ptr<vector<WorldObject> > scene) = 0;

	/**
	 * Destructor
	 */
	virtual ~Renderer();

};

} /* namespace AvoidTheBug3D */

#endif /* RENDERER_H_ */
