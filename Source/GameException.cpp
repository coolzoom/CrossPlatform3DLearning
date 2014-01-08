/*
 * GameException.cpp
 *
 *  Created on: Dec 29, 2013
 *      Author: Dimitri Kourkoulis
 */

#include "GameException.h"

namespace AvoidTheBug3D {

GameException::GameException() {


}

GameException::GameException(string message) {
	this->message = message;
}

const char* GameException::what() const throw () {
	return message.c_str();
}


GameException::~GameException() throw() {
	// TODO Auto-generated destructor stub
}

} /* namespace AvoidTheBug3D */

