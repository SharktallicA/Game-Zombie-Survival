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
	const unsigned char charMANHOLE = 'M';
	const unsigned char charZOMBIE = 'Z';
	const unsigned int intSLEEP = 128;

	//game variables
	bool boolIsExpert;
	coord board;

	//game objects
	Human player;
	vector<Manhole> manholes;
	vector<Zombie> zombies;

	void getDifficulty();
	void createManholes();
	void createZombies();
	void createHuman();

	void printBoard();

	void update();
	coord updateHuman();
	vector<coord> updateZombies();
	void drawPlayer(coord);
	void drawManholes();
	void drawZombies(vector<coord>);

	void postUpdate();
	bool checkHuman();
	vector<coord> checkZombies();
public:
	Game() { Utility::setColour(WHITE, BLACK); };
	bool run();
};