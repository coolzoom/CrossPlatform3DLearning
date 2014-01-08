/*
 * GameException.cpp
 *
 *  Created on: Dec 29, 2013
 *      Author: Dimitri Kourkoulis
 */

#include "GameException.h"

namespace AvoidTheBug3D {

GameException::GameException() {
	message = 0;

}

GameException::GameException(char* message) {
	this->message = message;
}

const char* GameException::what() const throw () {
	return message;
}


GameException::~GameException() throw() {
	// TODO Auto-generated destructor stub
}

} /* namespace AvoidTheBug3D */

