#include "Model.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include "GameException.h"

using namespace std;
using namespace boost;
namespace AvoidTheBug3D {

Model::Model(string filename, const boost::shared_ptr<Configuration> &cfg,
		const boost::shared_ptr<GameLog> &log) {
	this->cfg = cfg;
	this->log = log;

	vertices = new vector<float *>();
	vertices->clear();
	faces = new vector<int *>();
	faces->clear();
	loadFromFile(filename);
}

Model::~Model(void) {
	if (vertices != NULL) {
		for (int i = 0; i != vertices->size(); ++i) {
			delete[] vertices->at(i);
		}
		vertices->clear();
		delete vertices;
	}

	if (faces != NULL) {
		for (int i = 0; i != faces->size(); ++i) {
			delete[] faces->at(i);
		}
		faces->clear();
		delete faces;
	}
}

void Model::loadFromFile(string fileLocation) {
	ifstream file((cfg->getHomeDirectory() + fileLocation).c_str());
	string line;
	if (file.is_open()) {
		while (getline(file, line)) {
			if (line[0] == 'v' || line[0] == 'f') {
				char_separator<char> sep(" ");
				tokenizer<char_separator<char> > tokens(line, sep);
				int idx = 0;

				if (line[0] == 'v') {
					float *v = new float[3];
					BOOST_FOREACH (const string& t, tokens){
						if (idx > 0) { // The first token is the vertice indicator
							v[idx - 1] = atof(t.c_str());
						}
						++idx;
					}
					vertices->push_back(v);
				}
				else
				{
					int *v = new int[3];
					BOOST_FOREACH (const string& t, tokens){
						if (idx > 0) { // The first token is face indicator
							v[idx - 1] = atoi(t.c_str());
						}
						++idx;
					}
					faces->push_back(v);
				}
			}
		}
		file.close();
	} else
		throw GameException(
				"Could not open file " + cfg->getHomeDirectory()
						+ fileLocation);

}

void Model::outputVertices() {
	int vectorCount = vertices->size();
	for (int idx = 0; idx != vectorCount; ++idx) {
		cout << "Vertice:" << vertices->at(idx)[0] << " - "
				<< vertices->at(idx)[1] << " - " << vertices->at(idx)[2]
				<< endl;
	}
}

int Model::getNumVertices() {
	return (int) this->vertices->size();
}

int Model::getNumFaces() {
	return (int) this->faces->size();
}

vector<float*>* Model::getVertices() {
	return vertices;
}

void Model::outputFaces() {
	int vectorCount = faces->size();
	for (int idx = 0; idx != vectorCount; ++idx) {
		cout << "Face:" << faces->at(idx)[0] << " - " << faces->at(idx)[1]
				<< " - " << faces->at(idx)[2] << endl;
	}
}

vector<int*>* Model::getFaces() {
	return faces;
}

}

