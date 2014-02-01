/*
 * Renderer.h
 *
 *  Created on: Jan 15, 2014
 *      Author: Dimitri Kourkoulis
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#ifndef SDLANDOPENGL
#define SDLANDOPENGL
//#define GLEW_STATIC
#define NO_SDL_GLEXT
#include "GL/glew.h" // It seems that, when using glew,
                      // we do not need to include gl.h,
                      // glext.h or glu.h (if we do include
					  // them, they need to be included after
                      // glew.
#include "SDL_opengl.h"
#include "SDL.h"
#endif //SDLANDOPENGL

#include <boost/smart_ptr.hpp>
#include "WorldObject.h"
#include <vector>
#include "Configuration.h"
#include "GameLog.h"
#include <boost/smart_ptr.hpp>

namespace AvoidTheBug3D {

//typedef unsigned int (*GL_CreateShader_Func)(unsigned int);

class Renderer {

protected:
	SDL_Surface *screen;
	SDL_Surface *icon;
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
	virtual void Init(int width, int height);

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
