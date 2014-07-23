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
	// TODO Auto-generated constructor stub

}

void RendererOpenGL21::Init(int width, int height) {
}

void RendererOpenGL21::DrawScene(
		boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > > scene) {
}

RendererOpenGL21::~RendererOpenGL21() {
	// TODO Auto-generated destructor stub
}
}
