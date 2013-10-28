#pragma once
#include <string>
using namespace std;

/// A game character
class GameCharacter
{
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
};

