#pragma once
#include "Utility.h"
#include "Entity.h"
#include <string>
#include <vector>

using namespace std;

class Game
{
private:
	//constants
	const int intBOARDX = 60;
	const int intBOARDY = 30;
	const unsigned char charBORDER = 178;
	const unsigned char charHUMAN = 'H';
	const unsigned char charZOMBIE = 'Z';

	//game variables
	string strDifficulty;

	//game objects
	Human player;
	vector<Zombie> zombies;

	void createHuman();
	void getDifficulty();
	void createZombies();

	void printHeader();
	void printBoard();

	void update();
public:
	Game() {};
	bool run();
};