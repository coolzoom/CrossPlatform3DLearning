#pragma once

#include <string>
#include <GL/gl.h>
#include <vector>
using namespace std;

/// A game character
class GameCharacter
{
private:
	vector<GLfloat**> objectTokens;
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
	void LoadFromFile(string fileLocation);

	/**
	 * Output vectors to stdout
	 */
	void OutputVectors();
};


