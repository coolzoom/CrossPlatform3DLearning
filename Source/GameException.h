/*
 * GameException.h
 *
 *  Created on: Dec 29, 2013
 *      Author: Dimitrios Kourkoulis
 */

#ifndef GAMEEXCEPTION_H_
#define GAMEEXCEPTION_H_

#include <exception>

using namespace std;

namespace AvoidTheBug3D {

class GameException : public exception  {
public:
	GameException();
	virtual ~GameException();
};

} /* namespace AvoidTheBug3D */

#endif /* GAMEEXCEPTION_H_ */
