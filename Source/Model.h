#pragma once

#include <string>
#include <GL/gl.h>
#include <vector>
using namespace std;

namespace AvoidTheBug3D {

/// A game character
class Model {
private:
	vector<GLfloat*> *vertices;
public:
	/**
	 * Initialisation of the game character
	 */
	Model(void);
	~Model(void);

	/**
	 * Load model from file
	 * @param fileLocation The file location
	 */
	void loadFromFile(string fileLocation);

	/**
	 * Output vertices to stdout
	 */
	void outputVertices();

	/**
	 * Render the model
	 */
	void render();
};

}
