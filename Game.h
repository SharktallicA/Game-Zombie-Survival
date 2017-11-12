#pragma once
#include "Utility.h"
#include <string>

using namespace std;

class Game
{
private:
	string strName;
	string strDifficulty;
	int intBoardSize;
public:
	Game() {};
	bool run();

	void configWindow();
	void getGameDetails();
};