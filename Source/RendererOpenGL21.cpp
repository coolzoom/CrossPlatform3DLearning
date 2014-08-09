/*
 * RendererOpenGL21.cpp
 *
 *  Created on: 22 Jul 2014
 *      Author: Dimitri Kourkoulis
 */

#include "RendererOpenGL21.h"
namespace AvoidTheBug3D {

RendererOpenGL21::RendererOpenGL21(boost::shared_ptr<Configuration> cfg,
		boost::shared_ptr<GameLog> log) :
		Renderer(cfg, log) {

	vertexShaderPath =
			"/Game/Shaders/OpenGL21/perspectiveMatrixLightedShader.vert";
	fragmentShaderPath = "/Game/Shaders/OpenGL21/textureShader.frag";

}

void RendererOpenGL21::Init(int width, int height) {
	Renderer::Init(width, height);
}

void RendererOpenGL21::DrawScene(
		boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > scene) {
}

RendererOpenGL21::~RendererOpenGL21() {
	// TODO Auto-generated destructor stub
}
}
