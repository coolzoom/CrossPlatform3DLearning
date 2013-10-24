#pragma once
#include <string>
using namespace std;
class GameCharacter
{
public:
	GameCharacter(void);
	~GameCharacter(void);

	void LoadFromFile(string fileLocation);
};

