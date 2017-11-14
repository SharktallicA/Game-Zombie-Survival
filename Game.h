#pragma once
#include "Utility.h"
#include "Entity.h"
#include <string>
#include <vector>

using namespace std;

class Game
{
private:
	string strDifficulty;
	int intBoardSize = 30;
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