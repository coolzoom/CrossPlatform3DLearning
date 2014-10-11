#ifndef GETTOKENS_H_
#define GETTOKENS_H_

#include <string>

using namespace std;

namespace AvoidTheBug3D {

	/**
	 * Separates a string into tokens, using the given character
	 * as a separator
	 *
	 * @param	input		  	The input string
	 * @param	sep			  	The separator
	 * @param [in,out]	tokens	The tokens
	 *
	 * @return	The number of tokens
	 */

	int getTokens(string input, char sep, string* tokens);
}

#endif /* GETTOKENS_H_ */