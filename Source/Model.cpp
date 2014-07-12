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

Model::Model(string filename, bool multiColour, bool indexedDrawing,
		const boost::shared_ptr<Configuration> &cfg,
		const boost::shared_ptr<GameLog> &log) {
	this->cfg = cfg;
	this->log = log;

	vertices = new vector<float *>();
	vertices->clear();
	facesVertexIndexes = new vector<int *>();
	facesVertexIndexes->clear();
	normals = new vector<float *>();
	normals->clear();
	facesNormalIndexes = new vector<int *>();
	facesNormalIndexes->clear();
	textureCoords = new vector<float *>();
	textureCoords->clear();
	textureCoordsIndexes = new vector<int *>();
	textureCoordsIndexes->clear();
	vertexData = NULL;
	vertexDataSize = 0;
	vertexDataComponentCount = 0;
	indexData = NULL;
	indexDataSize = 0;
	indexDataIndexCount = 0;
	normalsData = NULL;
	normalsDataSize = 0;
	normalsDataComponentCount = 0;
	textureCoordsData = NULL;
	textureCoordsDataSize = 0;
	textureCoordsDataComponentCount = 0;
	this->multiColour = multiColour;
	this->indexedDrawing = indexedDrawing;
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

	if (facesVertexIndexes != NULL) {
		for (int i = 0; i != facesVertexIndexes->size(); ++i) {
			delete[] facesVertexIndexes->at(i);
		}
		facesVertexIndexes->clear();
		delete facesVertexIndexes;
	}

	if (normals != NULL) {
		for (int i = 0; i != normals->size(); ++i) {
			delete[] normals->at(i);
		}
		normals->clear();
		delete normals;
	}

	if (facesNormalIndexes != NULL) {
		for (int i = 0; i != facesNormalIndexes->size(); ++i) {
			delete[] facesNormalIndexes->at(i);
		}
		facesNormalIndexes->clear();
		delete facesNormalIndexes;
	}

	if (textureCoords != NULL) {
		for (int i = 0; i != textureCoords->size(); ++i) {
			delete[] textureCoords->at(i);
		}
		textureCoords->clear();
		delete textureCoords;
	}

	if (textureCoordsIndexes != NULL) {
		for (int i = 0; i != textureCoordsIndexes->size(); ++i) {
			delete[] textureCoordsIndexes->at(i);
		}
		textureCoordsIndexes->clear();
		delete textureCoordsIndexes;
	}

	if (vertexData != NULL) {
		delete[] vertexData;
	}

	if (indexData != NULL) {
		delete[] indexData;
	}

	if (normalsData != NULL) {
		delete[] normalsData;
	}

	if (textureCoordsData != NULL) {
		delete[] textureCoordsData;
	}
}

void Model::loadFromFile(string fileLocation) {
	if (vertices->size() != 0) {
		throw GameException(
				"Illegal attempt to reload model. Please use another object.");
	}
	ifstream file((cfg->getHomeDirectory() + fileLocation).c_str());
	string line;
	if (file.is_open()) {
		while (getline(file, line)) {
			if (line[0] == 'v' || line[0] == 'f') {
				char_separator<char> sep(" ");
				tokenizer<char_separator<char> > tokens(line, sep);
				int idx = 0;

				if (line[0] == 'v' && line[1] == 'n') {
					// get vertex normal
					float *vn = new float[3];
					BOOST_FOREACH (const string& t, tokens) {
						if (idx > 0) { // The first token is the vertex normal indicator
							vn[idx - 1] = atof(t.c_str());
						}
						++idx;
					}
					normals->push_back(vn);
				} else if (line[0] == 'v' && line[1] == 't') {
					float *vt = new float[2];
					BOOST_FOREACH (const string& t, tokens) {
						if (idx > 0) { // The first token is the vertex texture coordinate indicator
							vt[idx - 1] = atof(t.c_str());
						}
						++idx;
					}
					textureCoords->push_back(vt);
				} else if (line[0] == 'v') {
					// get vertex
					float *v = new float[3];
					BOOST_FOREACH (const string& t, tokens) {
						if (idx > 0) { // The first token is the vertex indicator
							v[idx - 1] = atof(t.c_str());
						}
						++idx;
					}
					vertices->push_back(v);
				} else {
					// get vertex index
					int *v = new int[3];
					int *n = NULL;
					int *textC = NULL;
					BOOST_FOREACH (const string& t, tokens) {

						if (idx > 0) { // The first token is face indicator
							if (t.find("//") != string::npos) { // normal index contained in the string
								// and texture coordinate index is missing
								if (n == NULL)
									n = new int[3];

								v[idx - 1] = atoi(
										t.substr(0, t.find("//")).c_str());
								n[idx - 1] = atoi(
										t.substr(t.find("//") + 2).c_str());
							} else if (t.find("/") != string::npos
									&& t.find("//") == string::npos) { // normal and texture coordinate index are
									// contained in the string
								if (n == NULL)
									n = new int[3];
								if (textC == NULL)
									textC = new int[3];
								char_separator<char> compsep("/");
								tokenizer<char_separator<char> > components(t,
										compsep);
								int componentIdx = 0;

								BOOST_FOREACH(const string &component, components) {
									switch (componentIdx) {
									case 0:
										v[idx - 1] = atoi(component.c_str());
										break;
									case 1:
										textC[idx - 1] = atoi(
												component.c_str());
										break;
									case 2:
										n[idx - 1] = atoi(component.c_str());
										break;
									}
									++componentIdx;
								}
							}

							else { // just the vertex index is contained in the string
								v[idx - 1] = atoi(t.c_str());
							}
						}
						++idx;
					}
					facesVertexIndexes->push_back(v);
					if (n != NULL)
						facesNormalIndexes->push_back(n);
					if (textC != NULL)
						textureCoordsIndexes->push_back(textC);
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
		cout << "Vertex:" << vertices->at(idx)[0] << " - "
				<< vertices->at(idx)[1] << " - " << vertices->at(idx)[2]
				<< endl;
	}
}

int Model::getNumVertices() {
	return (int) this->vertices->size();
}

int Model::getNumFaces() {
	return (int) this->facesVertexIndexes->size();
}

vector<float*>* Model::getVertices() {
	return vertices;
}

void Model::outputFaces() {
	int vectorCount = facesVertexIndexes->size();
	for (int idx = 0; idx != vectorCount; ++idx) {
		cout << "Face:" << facesVertexIndexes->at(idx)[0] << " - "
				<< facesVertexIndexes->at(idx)[1] << " - "
				<< facesVertexIndexes->at(idx)[2] << endl;
	}
}

vector<int*>* Model::getFaces() {
	return facesVertexIndexes;
}

float* Model::getVertexData() {
	if (vertexData == NULL && indexedDrawing) {
		if (multiColour) {
			throw GameException(
					"Multicolour not supported in combination with indexed drawing");
		}

		int vertexDataNumElements = vertices->size() * 4;
		vertexDataSize = vertexDataNumElements * sizeof(float);

		vertexData = new float[vertexDataNumElements];

		vertexDataComponentCount = 0;

		BOOST_FOREACH(const float* vertex, *vertices) {
			for (int coordIdx = 0; coordIdx != 3; ++coordIdx) {
				vertexData[vertexDataComponentCount] = vertex[coordIdx];
				++vertexDataComponentCount;
			}
			vertexData[vertexDataComponentCount] = 1.0f;
			++vertexDataComponentCount;
		}

	} else if (vertexData == NULL) {
		int numFaces = facesVertexIndexes->size();
		int numVertexComponents = numFaces * 12; // faces * num vertices per face * 4 (3 components + 1)
		int vertexDataNumElements = numVertexComponents * (multiColour ? 2 : 1); // components multiplied
																				 // by 2 if random colours
																				 // will be added
		vertexData = new float[vertexDataNumElements];

		vertexDataSize = vertexDataNumElements * sizeof(float);

		vertexDataComponentCount = 0;
		int colourIndex = 0;
		// Face
		for (int faceIdx = 0; faceIdx != numFaces; ++faceIdx) {
			// Vertex
			for (int vertexIdx = 0; vertexIdx != 3; ++vertexIdx) {
				// Coordinate
				for (int coordIdx = 0; coordIdx != 3; ++coordIdx) {

					vertexData[vertexDataComponentCount] =
							vertices->at(
									facesVertexIndexes->at(faceIdx)[vertexIdx]
											- 1)[coordIdx];
					++vertexDataComponentCount;

					// w component
					if (coordIdx == 2) {
						vertexData[vertexDataComponentCount] = 1.0f;
						++vertexDataComponentCount;

						if (multiColour) {
							// Add random colours for each face to the data.

							// Colour rotation
							if (vertexIdx == 0) {
								if (colourIndex == 3) {
									colourIndex = 0;
								} else {
									++colourIndex;
								}
							}

							float colour[] = { 0.0f, 0.0f, 0.0f, 1.0f };

							switch (colourIndex) {

							// Red
							case 0:
								colour[0] = 1.0f;
								break;

								// Yellow
							case 1:
								colour[0] = 1.0f;
								colour[1] = 1.0f;
								break;

								// Blue
							case 2:
								colour[2] = 1.0f;
								break;

								// White
							case 3:
								colour[0] = 1.0f;
								colour[1] = 1.0f;
								colour[2] = 1.0f;
								break;

								// Green (should not appear)
							default:
								colour[1] = 1.0f;
								break;
							}
							memcpy(&vertexData[vertexDataComponentCount - 4 // -4 to correspond to the
																			// vector just added (back
																			// 4 places in the second
																			// half of the data array
							+ numVertexComponents], colour, 4 * sizeof(float));
						} // if multiColour
					} // w component
				} // Coordinate
			} // Vertex
		} // Face

	} // if vertexData == NULL

	return vertexData;
}

unsigned int * Model::getIndexData() {

	if (indexData == NULL && indexedDrawing) {
		int numIndexes = facesVertexIndexes->size() * 3;
		indexDataSize = numIndexes * sizeof(int);

		indexData = new unsigned int[numIndexes];

		indexDataIndexCount = 0;

		BOOST_FOREACH(const int* face, *facesVertexIndexes) {
			for (int indexIdx = 0; indexIdx != 3; ++indexIdx) {
				indexData[indexDataIndexCount] = face[indexIdx] - 1; // -1 because Wavefront indexes
																	 // are not 0 based
				++indexDataIndexCount;
			}
		}
	}
	return indexData;
}

void Model::outputVertexData() {
	cout << endl << "Number of faces: " << facesVertexIndexes->size() << endl;
	cout << "Total number of components: " << vertexDataComponentCount << endl;
	cout << "Multi-colour: " << multiColour << endl;
	int iterations = vertexDataComponentCount * (multiColour ? 2 : 1);
	for (int cnt = 0; cnt != iterations; ++cnt) {
		if (cnt % 4 == 0)
			cout << endl;
		cout << vertexData[cnt] << " ";
	}
	cout << endl;
}

void Model::outputIndexData() {
	cout << endl << "Index data element count: " << indexDataIndexCount << endl;
	for (int cnt = 0; cnt != indexDataIndexCount; ++cnt) {
		if (cnt % 3 == 0)
			cout << endl;
		cout << indexData[cnt] << " ";
	}
	cout << endl;
}

int Model::getVertexDataComponentCount() {
	return vertexDataComponentCount;
}

int Model::getVertexDataSize() {
	return vertexDataSize;
}

bool Model::isIndexedDrawing() const {
	return indexedDrawing;
}

int Model::getIndexDataSize() const {
	return indexDataSize;
}

bool Model::isMultiColour() const {
	return multiColour;
}

int Model::getIndexDataIndexCount() const {
	return indexDataIndexCount;
}

float* Model::getNormalsData() {

// Create an array of normal components which corresponds
// by index to the array of vertex components
	if (normalsData == NULL) {

		if (vertexDataComponentCount == 0) {
			throw GameException(
					"There are no vertices or vertex data has not yet been created.");
		}

		// -1 for each vertex data component, because the normals data has three components
		// per row
		normalsDataComponentCount = vertexDataComponentCount
				- vertexDataComponentCount / 4;
		normalsDataSize = normalsDataComponentCount * sizeof(float);

		normalsData = new float[normalsDataComponentCount];

		int faceVertexArrayIndex = 0;

		BOOST_FOREACH(const int* faceVertexIndex, *facesVertexIndexes) {
			for (int vertexIndex = 0; vertexIndex != 3; ++vertexIndex) {
//				cout << "Setting normal at " << 3 * (faceVertexIndex[vertexIndex] - 1)
//						<< " to normal index "
//						<< facesNormalIndexes->at(faceVertexArrayIndex)[vertexIndex]
//						<< endl;
				for (int normalsDataComponent = 0; normalsDataComponent != 3;
						++normalsDataComponent) {
					normalsData[3 * (faceVertexIndex[vertexIndex] - 1)
							+ normalsDataComponent] =
							normals->at(
									facesNormalIndexes->at(faceVertexArrayIndex)[vertexIndex]
											- 1)[normalsDataComponent];

//					cout << "  * Setting at " << 3 * (faceVertexIndex[vertexIndex] - 1)
//							+ vertexComponent << " to " << normals->at(facesNormalIndexes->at(faceVertexArrayIndex)[vertexIndex] - 1)[vertexComponent] << endl;

				}
			}
			++faceVertexArrayIndex;
		}
	}
	return normalsData;
}

void Model::outputNormalsData() {
	if (!multiColour) {
		cout << "Normals data" << endl;
		cout << "Component count: " << normalsDataComponentCount;

		for (int cnt = 0; cnt != normalsDataComponentCount; ++cnt) {
			if (cnt % 3 == 0)
				cout << endl;
			cout << normalsData[cnt] << " ";
		}
		cout << endl;
	} else {
		cout << "No normals in random colours model" << endl;
	}
}

int Model::getNormalsDataSize() const {
	return normalsDataSize;
}

int Model::getNormalsDataComponentCount() const {
	return normalsDataComponentCount;
}

float* Model::getTextureCoordsData() {
// Create an array of texture coordinates components which corresponds
// by index to the array of vertex components
	if (textureCoordsData == NULL) {

		if (vertexDataComponentCount == 0) {
			throw GameException(
					"There are no vertices or vertex data has not yet been created.");
		}

		// -2 for each vertex data component, because the texture coorddinates data
		// has two components per row
		textureCoordsDataComponentCount = vertexDataComponentCount
				- 2 * (vertexDataComponentCount / 4);
		textureCoordsDataSize = textureCoordsDataComponentCount * sizeof(float);

		textureCoordsData = new float[textureCoordsDataComponentCount];

		int faceVertexArrayIndex = 0;

		BOOST_FOREACH(const int* faceVertexIndex, *facesVertexIndexes) {
			for (int vertexIndex = 0; vertexIndex != 3; ++vertexIndex) {

				for (int textureCoordsComponent = 0;
						textureCoordsComponent != 2; ++textureCoordsComponent) {
					textureCoordsData[2 * (faceVertexIndex[vertexIndex] - 1)
							+ textureCoordsComponent] =
							textureCoords->at(
									facesNormalIndexes->at(faceVertexArrayIndex)[vertexIndex]
											- 1)[textureCoordsComponent];
				}
			}
			++faceVertexArrayIndex;
		}
	}
	return textureCoordsData;
}

void Model::outputTextureCoordsData() {
	if (!multiColour) {
		cout << "Texture coordinates data" << endl;
		cout << "Component count: " << textureCoordsDataComponentCount;

		for (int cnt = 0; cnt != textureCoordsDataComponentCount; ++cnt) {
			if (cnt % 2 == 0)
				cout << endl;
			cout << textureCoordsData[cnt] << " ";
		}
		cout << endl;
	} else {
		cout << "No texture coordinates in random colours model" << endl;
	}
}

int Model::getTextureCoordsDataSize() const {
	return textureCoordsDataSize;
}

int Model::getTextureCoordsDataComponentCount() const {
	return textureCoordsDataComponentCount;
}

}

