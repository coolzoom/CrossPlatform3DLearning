#include "GameCharacter.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

GameCharacter::GameCharacter(void) {
	vertices = new vector<GLfloat *>();
	vertices->clear();
}

GameCharacter::~GameCharacter(void) {
	if (vertices != NULL) {
		for (int i=0; i != vertices->size(); ++i) {
			delete[] vertices->at(i);
		}
		vertices->clear();
		delete vertices;
	}
}

void GameCharacter::loadFromFile(string fileLocation) {
	ifstream file(fileLocation.c_str());
	string line;
	if (file.is_open()) {
		while (getline(file, line)) {
			if (line[0] == 'v') {
				char_separator<char> sep(" ");
				tokenizer<char_separator<char> > tokens(line, sep);
				int idx = 0;
				GLfloat *v = new GLfloat[3];
				BOOST_FOREACH (const string& t, tokens) {
					if (idx > 0) {
						v[idx - 1] = atof(t.c_str());
					}
					++idx;
				}
				vertices->push_back(v);
			}
		}
		file.close();
	} else
		cout << "Could not open file." << endl;

}

void GameCharacter::outputVertices() {
	int vectorCount = vertices->size();
	for (int idx = 0; idx != vectorCount; ++idx) {
		cout << "Vertice:" << vertices->at(idx)[0] << " - "
				<< vertices->at(idx)[1] << " - " << vertices->at(idx)[2]
				<< endl;
	}
}

void GameCharacter::render() {
	//glBegin(GL_TRIANGLES);

	//glEnd();
}
