/*
 * Renderer.h
 *
 *  Created on: Dec 26, 2013
 *      Author: Dimitri Kourkoulis
 */

#ifndef RENDEREROPENGL14_H_
#define RENDEREROPENGL14_H_



#include "GameLog.h"
#include "Renderer.h"

namespace AvoidTheBug3D {

const GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
const GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat LightPosition[] = { -5.0f, 0.0f, 2.0f, 1.0f };

/**
 * Rendering class
 */
class RendererOpenGL14 : public Renderer {
private:
	float angle;

	GLuint texture[3];

public:
	/**
	 * Constructor
	 * @param log The logger class to be used
	 */
	RendererOpenGL14( boost::shared_ptr<Configuration> cfg,
			 boost::shared_ptr<GameLog> log);

	void Init(int width, int height);

	void DrawScene(boost::shared_ptr<vector<WorldObject> > scene);

	/**
	 * Destructor
	 */
	virtual ~RendererOpenGL14();
};

} /* namespace AvoidTheBug3D */

#endif /* RENDEREROPENGL14_H_ */
