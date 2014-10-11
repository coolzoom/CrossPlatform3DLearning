/*
* GameMath.h
*
*  Created on: Oct 11, 2014
*      Author: Dimitri Kourkoulis
*/

#ifndef GAMEMATH_H_
#define GAMEMATH_H_

#include <glm/glm.hpp>

#define ROUND_2_DECIMAL(x) (floorf(100 * x + 0.5) / 100)

namespace AvoidTheBug3D {

	/**
	* Rotation transformation for rotating around the X axis
	* @param angle The angle to rotate by, in radians.
	* @return The X rotation matrix
	*/
	glm::mat4x4* rotateX(const float angle);

	/**
	* Rotation transformation for rotating around the Y axis
	* @param angle The angle to rotate by, in radians.
	* @return The Y rotation matrix
	*/
	glm::mat4x4* rotateY(const float angle);

	/**
	* Rotation transformation for rotating around the Z axis
	* @param angle The angle to rotate by, in radians.
	* @return The Z rotation matrix
	*/
	glm::mat4x4* rotateZ(const float angle);
}
#endif /* GAMEMATH_H_ */