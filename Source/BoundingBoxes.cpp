/*
* BoundingBoxes.cpp
*
*  Created on: Oct 10, 2014
*      Author: Dimitri Kourkoulis
*/

#include "BoundingBoxes.h"
#include <fstream>
#include "GameException.h"
#include "GetTokens.h"
#include <stdlib.h>

namespace AvoidTheBug3D {

	/**
	* Constructor
	* 
	* @param	cfg	The configuration.
	* @param	log	The log.
	*/
	BoundingBoxes::BoundingBoxes(const boost::shared_ptr<Configuration> cfg, const boost::shared_ptr<GameLog> log) {
		this->cfg = cfg;
		this->log = log;

		vertices = new vector<float *>();
		vertices->clear();
		facesVertexIndexes = new vector<int *>();
		facesVertexIndexes->clear();
	}

	BoundingBoxes::~BoundingBoxes() {
		if (vertices != NULL)
		{
			for (int i = 0; i != vertices->size(); ++i)
			{
				delete[] vertices->at(i);
			}
			vertices->clear();
			delete vertices;
			vertices = NULL;
		}

		if (facesVertexIndexes != NULL)
		{
			for (int i = 0; i != facesVertexIndexes->size(); ++i)
			{
				delete[] facesVertexIndexes->at(i);
			}
			facesVertexIndexes->clear();
			delete facesVertexIndexes;
			facesVertexIndexes = NULL;
		}
	}

	void BoundingBoxes::loadFromFile( string fileLocation )
	{
		if (vertices->size() != 0)
		{
			throw GameException(
				"Illegal attempt to reload bounding boxes. Please use another object.");
		}
		ifstream file((cfg->getHomeDirectory() + fileLocation).c_str());
		string line;
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (line[0] == 'v' || line[0] == 'f')
				{
					string *tokens = new string[5]; // Max 5 such tokens in the specific kind of
					// Wavefront file

					int numTokens = getTokens(line, ' ', tokens);

					int idx = 0;

					if (line[0] == 'v')
					{
						// get vertex
						float *v = new float[4];

						for (int tokenIdx = 0; tokenIdx < numTokens; ++tokenIdx)
						{
							string t = tokens[tokenIdx];
							if (idx > 0)   // The first token is the vertex indicator
							{
								v[idx - 1] = (float) atof(t.c_str());
							}
							++idx;
						}
						vertices->push_back(v);
					}
					else
					{
						// get vertex index
						int *v = new int[4];

						for (int tokenIdx = 0; tokenIdx < numTokens; ++tokenIdx)
						{
							string t = tokens[tokenIdx];
							if (idx > 0)   // The first token is face indicator
							{
								v[idx - 1] = atoi(t.c_str());
							}
							++idx;
						}
						facesVertexIndexes->push_back(v);

					}

					if (tokens != NULL)
					{
						delete[] tokens;
					}
				}
			}
		}
		file.close();
	}

}