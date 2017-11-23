#include "Game.h"

Game::Game()
{
	Utility::setColour(WHITE, BLACK);
}
bool Game::run()
{
	//purpose: handles game's operation
	//pre-condition: inside a while loop (e.g. while(game.run());) to allow continous play

	//set up game
	getDifficulty();
	createHuman();
	createZombies();

	//set up window
	Utility::setWindowTitle("Zombie Survival");
	if (boolIsExpert)
		Utility::setWindowSize(830, 1000);
	else
		Utility::setWindowSize(595, 1000);

	//run game loop
	printBoard();
	while (player.checkIfAlive())
	{
		update();
		Sleep(50);
	}

	//end game
	return Utility::getYesNo("Play again (y/n)? ");
}

void Game::createHuman()
{
	//purpose: configure's the human's start properties
	player = Human(Utility::getString("Enter your name: "), coord(Utility::generateNumber(1, board.X), Utility::generateNumber(1, board.Y)));
}
void Game::getDifficulty()
{
	//purpose: asks user for input on difficulty
	
	boolIsExpert = Utility::getYesNo("Use expert difficulty (y/n)? ");
	if (boolIsExpert)
		board = coord(90, 30);
	else
		board = coord(60, 30);
}
void Game::createZombies()
{
	//purpose: generates a bunch of zombies (based on difficulty) and randomises their location

	int intToMake = 10; //base zombie amount for normal difficulty ***DECREASED FOR TESTING***
	if (boolIsExpert)
		intToMake *= 3; //factor in expert difficulty modifier

	for (int intIndex = 0; intIndex < intToMake; intIndex++)
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
						if (intX == zombie.getPos().X && intY == zombie.getPos().Y)
							boolIsUnique = false;
					}
				}
			}

			//prevent zombie from being spanwed on player
			if (boolIsUnique)
			{
				if (intX == player.getPos().X && intY == player.getPos().Y)
					boolIsUnique = false;
			}
		}
		zombies.push_back(Zombie(intIndex, coord(intX, intY)));
	}
}

void Game::printBoard()
{
	//purpose: prints out board with all entity starting positions in place

	//draw board rows
	Utility::setColour(LIGHT_BLUE, LIGHT_BLUE);
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
	drawPlayer(coord(-1, -1)); //-1 flags that the drawPlayer() method should not erase a previous path since no exits

	//draw zombies
	vector<coord> emptyVector;
	drawZombies(emptyVector); //emptyVector passed to flag that the drawZombies() method should not erase a previous path since no exits

	//draw event board
	Utility::setColour(WHITE, BLACK);
	Utility::moveCursor(0, 37);
	cout << "Events: ";
}

void Game::update()
{
	//purpose: moves game forward at every turn; handles movement and redrawing

	//update human
	drawPlayer(updateHuman());

	//update zombies
	drawZombies(updateZombies());

	//post-update procedures
	events(); 
	intMove++;
}
coord Game::updateHuman()
{
	coord playerLast;

	playerLast.X = player.getPos().X;
	playerLast.Y = player.getPos().Y;
	player.move(board);
	return playerLast;
}
vector<coord> Game::updateZombies()
{
	vector<coord> zombiesLast;

	for (unsigned int intIndex = 0; intIndex < zombies.size(); intIndex++)
	{
		coord zombieLast;
		zombieLast.X = zombies[intIndex].getPos().X;
		zombieLast.Y = zombies[intIndex].getPos().Y;
		zombiesLast.push_back(zombieLast);
		zombies[intIndex].move(board, zombies);
	}
	return zombiesLast;
}
void Game::drawPlayer(coord playerLast)
{
	//pre-condition: a previous player position is provided for path erasing, or a 'dummy' coord with -1 to flag for no path erasing

	Utility::setColour(LIGHT_YELLOW, BLACK);

	//erase human char
	if (playerLast.X != -1 && playerLast.Y != -1)
	{
		Utility::moveCursor(4 + playerLast.X, 3 + playerLast.Y);
		cout << " ";
	}

	//draw human's new position 
	Utility::moveCursor(4 + player.getPos().X, 3 + player.getPos().Y);
	cout << charHUMAN;
}
void Game::drawZombies(vector<coord> zombiesLast)
{
	//pre-condition: previous zombie positions are provided for path erasing, or a 'dummy' vector with no coords to flag for no path erasing

	Utility::setColour(LIGHT_RED, BLACK);

	for (unsigned int intIndex = 0; intIndex < zombies.size(); intIndex++)
	{
		if (zombies[intIndex].checkIfAlive())
		{
			//erase zombie's old position
			if (zombiesLast.size() != 0)
			{
				Utility::moveCursor(4 + zombiesLast[intIndex].X, 3 + zombiesLast[intIndex].Y);
				cout << " ";
			}

			//draw zombie's new position
			Utility::moveCursor(4 + zombies[intIndex].getPos().X, 3 + zombies[intIndex].getPos().Y);
			cout << charZOMBIE;
		}
	}
}

void Game::events()
{
	//purpose: checks for and post events

	Utility::moveCursor(0, 38 + intEventCount); //moves cursor the event board's next blank line

												//erase zombies from the board
	Utility::setColour(WHITE, BLACK);
	vector<coord> coordDeaths = checkZombies();
	for (auto death : coordDeaths)
	{
		Utility::moveCursor(4 + death.X, 3 + death.Y);
		cout << " ";
		intEventCount++;
	}
}
vector<coord> Game::checkZombies()
{
	//purpose: checks if any zombies have died and posts their death onto the event board
	//usage: this method MUST only be called in events() method since the cursor position has to be set beforehand (ie. cursor is at event board position)

	vector<coord> coordDeaths; //contains all death locations to be used elsewhere

	for (unsigned int intX = 0; intX < zombies.size(); intX++)
	{
		for (unsigned int intY = 0; intY < zombies.size(); intY++)
		{
			if (zombies[intX].checkIfAlive() && zombies[intY].checkIfAlive() && zombies[intX].getID() != zombies[intY].getID() && zombies[intX].getPos().X == zombies[intY].getPos().X && zombies[intX].getPos().Y == zombies[intY].getPos().Y) //checks for a collision
			{
				zombies[intX].kill();
				zombies[intY].kill();
				coordDeaths.push_back(coord(zombies[intX].getPos().X, zombies[intX].getPos().Y));
				cout << "Move " << intMove << ": zombies " << zombies[intX].getID() << " and " << zombies[intY].getID() << " have died due to a collision at " << zombies[intX].getPos().X << "x" << zombies[intX].getPos().Y << "!" << endl;
			}
		}
	}
	return coordDeaths;
}