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
	ifstream file(fileLocation.c_str());
	string line;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			cout << line << endl;
		}
		file.close();
	}
	else cout << "Could not open file." << endl;
		
}
