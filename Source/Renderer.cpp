#include "Renderer.h"
#include "GameException.h"

namespace AvoidTheBug3D {

Renderer::Renderer(boost::shared_ptr<Configuration> cfg,
		boost::shared_ptr<GameLog> log) {
	this->cfg = cfg;
	this->log = log;
}

Renderer::~Renderer() {

	LOGINFO("Renderer superclass destructor running");
}

void Renderer::Init(int width, int height) {

	//SDL_WM_SetIcon(icon, NULL);



}

} // AvoidTheBug3D

