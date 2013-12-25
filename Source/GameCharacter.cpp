#include "GameCharacter.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

GameCharacter::GameCharacter(void) {
	objectTokens = new vector<GLfloat *>();
	objectTokens->clear();
}

GameCharacter::~GameCharacter(void) {
	if (objectTokens != NULL) {
		for (int i; i != objectTokens->size(); ++i) {
			delete[] objectTokens->at(i);
		}
		objectTokens->clear();
		delete objectTokens;
	}
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
				GLfloat *v = new GLfloat[3];
				BOOST_FOREACH (const string& t, tokens) {
					if (idx > 0) {
						cout << "Loading " << atof(t.c_str()) << endl;
						v[idx - 1] = atof(t.c_str());
						cout << "done." << endl;
					}
					++idx;
				}
				cout << "Pushing tokens" << endl;
				objectTokens->push_back(v);
				cout << "Pushed" << endl;
			}
		}
		file.close();
	} else
		cout << "Could not open file." << endl;

}

void GameCharacter::OutputVectors() {
	cout << "About to output vectors" << endl;
	int vectorCount = objectTokens->size();
	for (int idx = 0; idx < vectorCount; ++idx) {
		cout << "Output " << idx << endl;
		cout << "Vector:" << objectTokens->at(idx)[0] << " - "
				<< objectTokens->at(idx)[1] << " - " << objectTokens->at(idx)[2]
				<< endl;
	}
}
