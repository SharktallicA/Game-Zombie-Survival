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
	coord board;
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
	Game() { board.X = 60; board.Y = 30; };
	bool run();
};