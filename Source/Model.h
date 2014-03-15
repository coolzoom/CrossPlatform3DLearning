#pragma once

#include <string>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <vector>
#include <boost/smart_ptr.hpp>
#include "GameLog.h"
#include "Configuration.h"

using namespace std;

namespace AvoidTheBug3D {

/// A game character
class Model {
private:
	vector<float*> *vertices;
	vector<int*> *faces;
	boost::shared_ptr<Configuration> cfg;
	boost::shared_ptr<GameLog> log;
	void loadFromFile(string fileLocation);
	float *vertexData;
	int vertexDataComponentCount;
	bool multiColour;
public:
	/**
	 * Initialisation of the model.
	 * @param fileLocation The model file location. This must be a Wavefront .obj file and it must have been
	 * exported from Blender with the options "Triangulate faces" and "Keep Vertex Order" checked
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
	 * Output faces to stdout
	 */
	void outputFaces();

	/**
	 * Get the number of vertices in the model
	 * @return The number of vertices
	 */
	int getNumVertices();

	/**
	 * Get the number of faces in the model
	 * @return The number of faces
	 */
	int getNumFaces();

	/**
	 * Get the vertices of the model
	 * @return The vertices
	 */
	vector<float*>* getVertices();

	/**
	 * Get the faces of the model
	 * @return The faces
	 */
	vector<int*>* getFaces();


	/**
	 * Get the vertex data, e.g. to be sent to glBindBuffer.
	 * The structure of the data can be defined via the Model's state.
	 * @return The vertex data
	 */
	float * getVertexData();


	/**
	 * Output the vertex data. The structure of the data can be defined
	 * via the Model's state.
	 */
	void outputVertexData();

	/**
	 * Get the number of components in the vertex data array
	 * @return The number of vertex data components
	 */
	int getVertexDataComponentCount();

	/**
	 * Set whether or not the vertex data that will be returned will
	 * contain random colours for each face.
	 * @param multiColour
	 */
	void setMultiColour(bool multiColour);
};

}
