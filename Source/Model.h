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

/// A model. It can be a simple object or a game character. It is loaded from a Wavefront .obj file.
class Model {
private:
	// Configuration & logging objects
	boost::shared_ptr<Configuration> cfg;
	boost::shared_ptr<GameLog> log;

	// Settings
	bool multiColour;
	bool indexedDrawing;

	// Basic data read from .obj file
	vector<float*> *vertices;
	vector<int*> *facesVertexIndexes;
	vector<float*> *normals;
	vector<int*> *facesNormalIndexes;
	vector<float*> *textureCoords;

	// Vertex data
	float *vertexData;
	int vertexDataSize;
	int vertexDataComponentCount;

	// Vertex index data
	unsigned int *indexData;
	int indexDataSize;
	int indexDataIndexCount;

	// Normals data
	float *normalsData;
	int normalsDataSize;
	int normalsDataComponentCount;


	// Load model from a Wavefront .obj file
	void loadFromFile(string fileLocation);

public:
	/**
	 * Initialisation of the model.
	 * @param fileLocation The model file location. This must be a Wavefront .obj file and it must have been
	 * exported from Blender with the options "Triangulate faces" and "Keep Vertex Order" checked
	 * @param multiColour Whether or not each face will be rendered with a random colour
	 * @param cfg The game configuration
	 * @param log The log
	 */
	Model(string fileLocation, bool multiColour, bool indexedDrawing,
			const boost::shared_ptr<Configuration> &cfg,
			const boost::shared_ptr<GameLog> &log);
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
	 * Get the index data, i.e. the indexes of each vertex to be drawn
	 * when the indexed drawing flag has been set.
	 * @return
	 */
	unsigned int * getIndexData();

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
	 * Output the index data.
	 */
	void outputIndexData();

	/**
	 * Get the number of components in the vertex data array
	 * @return The number of vertex data components
	 */
	int getVertexDataComponentCount();

	/**
	 * Get the size of the vertex data, in bytes.
	 * @return The size of the vertex data
	 */
	int getVertexDataSize();

	/**
	 * Is the model in indexed drawing mode?
	 * @return True if in indexed drawing mode, false otherwise
	 */
	bool isIndexedDrawing() const;

	/**
	 * Get the size of the index data
	 * @return The size of the index data
	 */
	int getIndexDataSize() const;

	/**
	 * Has the model been set to be drawn in random multiple colours?
	 * @return True if the model has been set to be drawn in random multiple colours, false otherwise
	 */
	bool isMultiColour() const;

	/**
	 * Get the number of index data elements
	 * @return The number of index data elements
	 */
	int getIndexDataIndexCount() const;

	/**
	 * Get the normals data
	 * @return The normals data
	 */
	float* getNormalsData();

	/**
	 * Output the normals data
	 */
	void outputNormalsData();

	/**
	 * Get the size of the normals data, in bytes
	 * @return The size of the normals data, in bytes
	 */
	int getNormalsDataSize() const;

	/**
	 * Get the total number of normals data components
	 * @return The total number of normals data components
	 */
	int getNormalsDataComponentCount() const;




};

}
