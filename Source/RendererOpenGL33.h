/*
 * RendererOpenGL33.h
 *
 *  Created on: Jan 19, 2014
 *      Author: Dimitri Kourkoulis
 */

#ifndef RENDEREROPENGL33_H_
#define RENDEREROPENGL33_H_

#include "Renderer.h"
#include <string>

using namespace std;

namespace AvoidTheBug3D {

class RendererOpenGL33: public Renderer {
private:
	string vertexShader;
	string fragmentShader;

	string loadShaderFromFile(string fileLocation);

public:
	RendererOpenGL33( boost::shared_ptr<Configuration> cfg,
			 boost::shared_ptr<GameLog> log);

	void Init(int width, int height);

	void DrawScene(boost::shared_ptr<vector<WorldObject> > scene);

	virtual ~RendererOpenGL33();
};

} /* namespace AvoidTheBug3D */

#endif /* RENDEREROPENGL33_H_ */
