/*
* GameMath.cpp
*
*  Created on: Oct 11, 2014
*      Author: Dimitri Kourkoulis
*/

#include "GameMath.h"

namespace AvoidTheBug3D {

	glm::mat4x4* rotateX(const float angle)
	{
		return new glm::mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, glm::cos(angle), -glm::sin(angle), 0.0f,
			0.0f, glm::sin(angle), glm::cos(angle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);
	}

	glm::mat4x4* rotateY(const float angle)
	{
		return new glm::mat4x4(glm::cos(angle), 0.0f, glm::sin(angle), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-glm::sin(angle), 0.0f, glm::cos(angle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);

	}

	glm::mat4x4* rotateZ(const float angle)
	{
		return new glm::mat4x4(glm::cos(angle), -glm::sin(angle), 0.0f,  0.0f,
			glm::sin(angle), glm::cos(angle), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);
	}

}