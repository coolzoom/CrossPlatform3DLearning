#include "GameCharacter.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

GameCharacter::GameCharacter(void) {
	objectTokens.clear();
}

GameCharacter::~GameCharacter(void) {
	for (int i; i<objectTokens.size(); ++i)
	{
		delete[] objectTokens[i];
	}
	objectTokens.clear();

}

void GameCharacter::LoadFromFile(string fileLocation) {
	ifstream file(fileLocation.c_str());
	string line;
	if (file.is_open()) {
		cout << "Tokens:" << endl;
		while (getline(file, line)) {
			if (line[0] == 'v') {
				char_separator<char> sep(" ");
				tokenizer<char_separator<char> > tokens(line, sep);
				int idx = 0;
				GLfloat **v = new GLfloat* [3];
				BOOST_FOREACH (const string& t, tokens) {
                    *v[idx] = atof(t.c_str());
                    idx ++;
				}
				objectTokens.push_back(v);
			}
		}
		file.close();
	} else
		cout << "Could not open file." << endl;

}

void GameCharacter::OutputVectors()
{
	int vectorCount = objectTokens.size();
	for (int idx; idx < vectorCount; idx++)
	{
		cout<<"Vector:" << *objectTokens[idx][0] << " - " << *objectTokens[idx][1] <<
				" - " << *objectTokens[idx][2];
	}
}
