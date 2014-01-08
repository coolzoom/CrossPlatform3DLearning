/*
 * GameException.h
 *
 *  Created on: Dec 29, 2013
 *      Author: Dimitrios Kourkoulis
 */

#ifndef GAMEEXCEPTION_H_
#define GAMEEXCEPTION_H_

#include <exception>
#include <string>

using namespace std;

namespace AvoidTheBug3D {

class GameException : public exception  {
private:
	string message;
public:
	GameException();
	GameException(string message);

	virtual const char* what() const throw();

	virtual ~GameException() throw();
};

} /* namespace AvoidTheBug3D */

#endif /* GAMEEXCEPTION_H_ */
