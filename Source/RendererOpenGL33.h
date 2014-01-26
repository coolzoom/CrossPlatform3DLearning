/*
 * RendererOpenGL33.h
 *
 *  Created on: Jan 19, 2014
 *      Author: Dimitri Kourkoulis
 */

#ifndef RENDEREROPENGL33_H_
#define RENDEREROPENGL33_H_

#include "GameLog.h"
#include "Renderer.h"

namespace AvoidTheBug3D {

class RendererOpenGL33: public Renderer {
public:
	RendererOpenGL33();

	void Init(int width, int height);

	void DrawScene(boost::shared_ptr<vector<WorldObject> > scene);

	virtual ~RendererOpenGL33();
};

} /* namespace AvoidTheBug3D */

#endif /* RENDEREROPENGL33_H_ */
