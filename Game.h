#pragma once
#include "coord.h"
#include "Entity.h"
#include "Utility.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Game
{
private:
	//constants
	const unsigned char charBORDER = 178;
	const unsigned char charHUMAN = 'H';
	const unsigned char charZOMBIE = 'Z';

	//game variables
	int intMove = 1;
	int intEventCount = 0;
	bool boolIsExpert;
	coord board;

	//game objects
	Human player;
	vector<Zombie> zombies;

	void createHuman();
	void getDifficulty();
	void createZombies();

	void printBoard();

	void update();
	coord updateHuman();
	vector<coord> updateZombies();
	void drawPlayer(coord);
	void drawZombies(vector<coord>);

	void events();
	vector<coord> checkZombies();
public:
	Game();
	bool run();
};