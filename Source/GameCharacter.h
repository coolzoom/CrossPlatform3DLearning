#pragma once

#include <string>
#include <GL/gl.h>
#include <vector>
using namespace std;

/// A game character
class GameCharacter
{
private:
	vector<GLfloat*> *vertices;
public:
	/**
	 * Initialisation of the game character
	 */
	GameCharacter(void);
	~GameCharacter(void);

	/**
	 * Load model from file
	 * @param fileLocation The file location
	 */
	void loadFromFile(string fileLocation);

	/**
	 * Output vertices to stdout
	 */
	void outputVertices();
};


