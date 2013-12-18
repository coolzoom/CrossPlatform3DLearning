#include "GameCharacter.h"
#include <iostream>
#include <fstream>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

GameCharacter::GameCharacter(void) {
}

GameCharacter::~GameCharacter(void) {
}

void GameCharacter::LoadFromFile(string fileLocation) {
	ifstream file(fileLocation.c_str());
	string line;
	if (file.is_open()) {
		cout << "Tokens:" << endl;
		while (getline(file, line)) {
			char_separator<char> sep(" ");
			tokenizer<char_separator<char> > tokens(line, sep);
			BOOST_FOREACH (const string& t, tokens){
			cout << t << endl;
		}
	}
	file.close();
}
else cout << "Could not open file." << endl;

}
