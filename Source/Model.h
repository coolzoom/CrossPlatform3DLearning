#pragma once

#include <string>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <GL/gl.h>
#include <vector>
#include <boost/smart_ptr.hpp>
#include "GameLog.h"
#include "Configuration.h"

using namespace std;

namespace AvoidTheBug3D {

/// A game character
class Model {
private:
	vector<GLfloat*> *vertices;
	boost::shared_ptr<Configuration> cfg;
	boost::shared_ptr<GameLog> log;
	void loadFromFile(string fileLocation);
public:
	/**
	 * Initialisation of the game character
	 * @param fileLocation The model file location (OBJ)
	 * @param cfg The game configuration
	 * @param log The log
	 */
	Model(string fileLocation, const boost::shared_ptr<Configuration> &cfg, const boost::shared_ptr<GameLog> &log);
	~Model(void);

	/**
	 * Output vertices to stdout
	 */
	void outputVertices();

	/**
	 * Render the model
	 */
	void render();

	/**
	 * Get the number of vertices in the model
	 * @return The number of vertices
	 */
	int getNumVertices();
};

}
