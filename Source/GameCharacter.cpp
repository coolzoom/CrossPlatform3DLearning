#include "GameCharacter.h"
#include <iostream>
#include <fstream>

GameCharacter::GameCharacter(void)
{
}


GameCharacter::~GameCharacter(void)
{
}

void GameCharacter::LoadFromFile( string fileLocation )
{
	ifstream file(fileLocation);
	if (file.is_open())
		file.close();
}
