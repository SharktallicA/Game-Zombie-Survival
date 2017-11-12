#include "Game.h"

bool Game::run()
{
	//purpose: handles game's operation
	//usage: inside a while loop (e.g. while(game.run());) to allow continous play

	//set up game
	configWindow();
	getGameDetails();

	//end game
	return Utility::getYesNo("Play again (y/n)? ");
}

void Game::configWindow()
{
	Utility::setWindowTitle("Zombie Survival");
	Utility::setWindowSize(800, 600);
}
void Game::getGameDetails()
{
	strName = Utility::getString("Enter your name: ");
	do
	{
		strDifficulty = Utility::getString("Enter difficulty (easy/medium/hard): ");
	} while(strDifficulty != "easy" && strDifficulty != "medium" && strDifficulty != "hard");
}