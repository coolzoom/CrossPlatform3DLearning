
#include "Renderer.h"

namespace AvoidTheBug3D {

Renderer::Renderer( boost::shared_ptr<Configuration> cfg,
		 boost::shared_ptr<GameLog> log) {
	this->cfg = cfg;
	this->log = log;

}

Renderer::~Renderer() {

}

}
