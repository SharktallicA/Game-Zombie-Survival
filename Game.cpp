#include "Game.h"

bool Game::run()
{
	//purpose: handles game's operation
	//usage: inside a while loop (e.g. while(game.run());) to allow continous play

	//set up window
	Utility::setWindowTitle("Zombie Survival");
	Utility::setWindowSize(800, 600);

	//set up game
	createHuman();
	getDifficulty();
	createZombies();

	//run game loop
	printHeader();
	printBoard();
	while (true)
		update();

	//end game
	return Utility::getYesNo("Play again (y/n)? ");
}

void Game::createHuman()
{
	//purpose: configure's the human's start properties

	//set player name
	player = Human(Utility::getString("Enter your name: "));

	//randomise player start location
	player.setX(Utility::generateNumber(0, 29));
	player.setY(Utility::generateNumber(0, 29));
}
void Game::getDifficulty()
{
	//purpose: asks user for input on difficulty

	do
	{
		strDifficulty = Utility::getString("Enter difficulty (novice/pro): ");
	} while(strDifficulty != "novice" && strDifficulty != "pro");
}
void Game::createZombies()
{
	//purpose: generates a bunch of zombies (based on difficulty) and randomises their location

	int intToMake = 10;
	if (strDifficulty == "pro")
		intToMake *= 2;

	for (int i = 0; i < intToMake; i++)
	{
		Zombie newZombie;
		bool boolIsUnique = false;
		int intX, intY;

		while (!boolIsUnique) //iterate until X-Y are unique
		{
			//generate two start numbers
			boolIsUnique = true;
			intX = Utility::generateNumber(0, 29);
			intY = Utility::generateNumber(0, 29);

			//prevent zombie from spawning on other zombies
			if (!zombies.empty())
			{
				for (auto zombie : zombies)
				{
					if (boolIsUnique)
					{
						if (intX == zombie.getX() && intY == zombie.getY())
							boolIsUnique = false;
					}
				}
			}

			//prevent zombie from being spanwed on player
			if (boolIsUnique)
			{
				if (intX == player.getX() && intY == player.getY())
					boolIsUnique = false;
			}
		}

		newZombie.setX(intX);
		newZombie.setY(intY);
		zombies.push_back(newZombie);
	}
}

void Game::printHeader()
{
	Utility::clearScreen();
	cout << "Zombie Survival | Khalid Ali";

}
void Game::printBoard()
{

}

void Game::update()
{

}