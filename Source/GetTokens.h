#ifndef GETTOKENS_H_
#define GETTOKENS_H_

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

	int getTokens(string input, char sep, string* tokens){
		int curPos = 0;
		int count = 0;

		int length = input.length();

		for (int idx = 0; idx < length; ++idx) {
			if (input[idx] == sep) {
				++count;
			}
		}
		++count;

		for (int idx = 0; idx < count; ++idx) {
			if (idx == count - 1) {
				tokens[idx] = input.substr(curPos);
			}
			else {

				size_t foundPos = input.find(sep, curPos);
				tokens[idx] = input.substr(curPos, foundPos - curPos);
				curPos = foundPos + 1;
			}
		}
		return count;
	}
}

#endif /* GETTOKENS_H_ */