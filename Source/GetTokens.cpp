/*
* GetTokens.cpp
*
*  Created on: Oct 11, 2014
*      Author: Dimitri Kourkoulis
*/

#include "GetTokens.h"

using namespace std;

namespace AvoidTheBug3D {

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
