/*
 * RendererOpenGL21.h
 *
 *  Created on: 22 Jul 2014
 *      Author: Dimitri Kourkoulis
 */

#ifndef RENDEREROPENGL21_H_
#define RENDEREROPENGL21_H_

#include "Renderer.h"
namespace AvoidTheBug3D {

class RendererOpenGL21: public Renderer {
public:
	RendererOpenGL21(boost::shared_ptr<Configuration> cfg,
			boost::shared_ptr<GameLog> log);
	virtual ~RendererOpenGL21();
};
}
#endif /* RENDEREROPENGL21_H_ */
