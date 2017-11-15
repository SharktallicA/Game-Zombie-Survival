#include "Game.h"

bool Game::run()
{
	//purpose: handles game's operation
	//usage: inside a while loop (e.g. while(game.run());) to allow continous play

	//set up window
	Utility::setWindowTitle("Zombie Survival");
	Utility::setWindowSize(800, 800);

	//set up game
	createHuman();
	getDifficulty();
	createZombies();

	//run game loop
	bool boolHumanAlive = true, boolZombiesAlive = true;
	printHeader();
	printBoard();
	while (boolHumanAlive && boolZombiesAlive)
		update();

	//end game
	return Utility::getYesNo("Play again (y/n)? ");
}

void Game::createHuman()
{
	//purpose: configure's the human's start properties
	player = Human(Utility::getString("Enter your name: "), Utility::generateNumber(1, board.X), Utility::generateNumber(1, board.Y));
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
		bool boolIsUnique = false;
		int intX, intY;

while (!boolIsUnique) //iterate until X-Y are unique
{
	//generate two start numbers
	boolIsUnique = true;
	intX = Utility::generateNumber(1, board.X);
	intY = Utility::generateNumber(1, board.Y);

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

zombies.push_back(Zombie(intX, intY));
	}
}

void Game::printHeader()
{
	//purpose: prints header of program

	Utility::clearScreen();
	cout << "Zombie Survival | Khalid Ali";
}
void Game::printBoard()
{
	//purpose: prints out board with all entity starting positions in place

	//draw board rows
	for (int intIndex = 0; intIndex <= board.X; intIndex++)
	{
		Utility::moveCursor(4 + intIndex, 3);
		cout << charBORDER;
		Utility::moveCursor(4 + intIndex, 4 + board.Y);
		cout << charBORDER;
	}

	//draw board columns
	for (int intIndex = 0; intIndex <= board.Y + 1; intIndex++)
	{
		Utility::moveCursor(4, 3 + intIndex);
		cout << charBORDER;
		Utility::moveCursor(5 + board.X, 3 + intIndex);
		cout << charBORDER;
	}

	//draw human
	Utility::moveCursor(4 + player.getX(), 3 + player.getY());
	cout << charHUMAN;

	//draw zombies
	for (auto zombie : zombies)
	{
		Utility::moveCursor(4 + zombie.getX(), 3 + zombie.getY());
		cout << charZOMBIE;
	}
}

void Game::update()
{
	//move human
	COORD playerLast;
	playerLast.X = player.getX();
	playerLast.Y = player.getY();
	player.move(board, zombies);

	//redraw human
	Utility::moveCursor(4 + playerLast.X, 3 + playerLast.Y);
	cout << " ";
	Utility::moveCursor(4 + player.getX(), 3 + player.getY());
	cout << charHUMAN;

	//move zombies
	vector<COORD> zombiesLast;
	for (auto zombie : zombies)
	{
		COORD zombieLast;
		zombieLast.X = zombie.getX();
		zombieLast.Y = zombie.getY();
		zombiesLast.push_back(zombieLast);
	}
	for (auto zombie : zombies)
		zombie.move(board);

	//redraw zombies
	for (int intIndex = 0; intIndex < zombies.size(); intIndex++)
	{
		Utility::moveCursor(4 + zombiesLast[intIndex].X, 3 + zombiesLast[intIndex].Y);
		cout << " ";
		Utility::moveCursor(4 + zombies[intIndex].getX(), 3 + zombies[intIndex].getY());
		cout << charZOMBIE;
	}
}