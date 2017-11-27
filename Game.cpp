#include "Game.h"

bool Game::run()
{
	//purpose: handles game's operation
	//pre-condition: inside a while loop (e.g. while(game.run());) to allow continous play

	//set up game
	getDifficulty();
	createManholes();
	createHuman();
	createZombies();

	//set up window
	Utility::setWindowTitle("Zombie Survival");
	Utility::setWindowSize(1000, 1000);

	//run game loop
	printBoard();
	while (player.checkIfAlive())
	{
		update();
		Sleep(50);
	}

	//end game
	Utility::clearScreen();
	Utility::setColour(WHITE, BLACK);
	return Utility::getYesNo("Play again (y/n)? ");
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
void Game::createManholes()
{
	//purpose: generates a bunch of manholes (based on difficulty) with random locations

	int intToMake = 5; //base manhole amount for normal difficulty
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

			//prevent manhole from spawning on other manholes
			if (!zombies.empty())
			{
				for (auto manhole : manholes)
				{
					if (boolIsUnique)
					{
						if (intX == manhole.getPos().X && intY == manhole.getPos().Y)
							boolIsUnique = false;
					}
				}
			}
		}
		manholes.push_back(Manhole(intIndex, coord(intX, intY)));
	}
}
void Game::createZombies()
{
	//purpose: generates a bunch of zombies (based on difficulty) and randomises their location

	int intToMake = 5; //base zombie amount for normal difficulty
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

			//prevent zombie from spawning on a manhole
			for (auto manhole : manholes)
			{
				if (boolIsUnique)
				{
					if (intX == manhole.getPos().X && intY == manhole.getPos().Y)
						boolIsUnique = false;
				}
			}
		}
		zombies.push_back(Zombie(zombies.size(), coord(intX, intY)));
	}
}
void Game::createHuman()
{
	//purpose: configure's the human's start properties

	bool boolIsUnique = false;
	coord coordPosition(0, 0);

	while (!boolIsUnique) //iterate until X-Y are unique
	{
		//generate two start numbers
		boolIsUnique = true;
		coordPosition = coord(Utility::generateNumber(1, board.X), Utility::generateNumber(1, board.Y));

		//prevent human from spawning on zombies
		for (auto zombie : zombies)
		{
			if (boolIsUnique)
			{
				if (coordPosition.X == zombie.getPos().X && coordPosition.Y == zombie.getPos().Y)
					boolIsUnique = false;
			}
		}

		//prevent human from spawning on a manhole
		for (auto manhole : manholes)
		{
			if (boolIsUnique)
			{
				if (coordPosition.X == manhole.getPos().X && coordPosition.Y == manhole.getPos().Y)
					boolIsUnique = false;
			}
		}
	}
	player = Human(Utility::getString("Enter your name: "), coordPosition);
}

void Game::printBoard()
{
	//purpose: prints out board with all entity starting positions in place

	Utility::clearScreen();

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

	//draw manholes
	drawManholes();

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

	if (checkHuman()) //update only continues if human is alive
	{
		//update manholes
		drawManholes();

		//update zombies
		drawZombies(updateZombies());

		//post-update procedures
		events();
		intMove++;
	}
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
		zombiesLast.push_back(zombies[intIndex].getPos());
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
void Game::drawManholes()
{
	Utility::setColour(LIGHT_PURPLE, BLACK);

	for (unsigned int intIndex = 0; intIndex < manholes.size(); intIndex++)
	{
		//draw manhole's new position
		Utility::moveCursor(4 + manholes[intIndex].getPos().X, 3 + manholes[intIndex].getPos().Y);
		cout << charMANHOLE;
	}
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
bool Game::checkHuman()
{
	//purpose: checks whether the human is in contact with zombies
	//pre-condition: this method is called in update() after the human has made a move

	for (auto zombie : zombies)
	{
		if (player.checkIfAlive())
		{
			if (player.getPos() == zombie.getPos())
				player.kill();
		}
	}
	return player.checkIfAlive();
}
vector<coord> Game::checkZombies()
{
	//purpose: checks if any zombies have died and posts their death onto the event board
	//pre-condition: this method MUST only be called in events() method since the cursor position has to be set beforehand (ie. cursor is at event board position)

	vector<coord> coordDeaths; //contains all death locations to be used elsewhere

	//check for collisions with manholes
	for (unsigned int intX = 0; intX < zombies.size(); intX++)
	{
		for (unsigned int intY = 0; intY < manholes.size(); intY++)
		{
			if (zombies[intX].checkIfAlive() && zombies[intX].getPos() == manholes[intY].getPos()) //checks for a collision
			{
				zombies[intX].kill();
				coordDeaths.push_back(coord(zombies[intX].getPos().X, zombies[intX].getPos().Y));
				cout << "Move " << intMove << ": zombie " << zombies[intX].getID() << " fell through a manhole at " << zombies[intX].getPos().X << "x" << zombies[intX].getPos().Y << "!" << endl;
			}
		}
	}

	//check for collisions with other zombies
	for (unsigned int intX = 0; intX < zombies.size(); intX++)
	{
		for (unsigned int intY = 0; intY < zombies.size(); intY++)
		{
			if (zombies[intX].checkIfAlive() && zombies[intY].checkIfAlive() && zombies[intX].getID() != zombies[intY].getID() && zombies[intX].getPos() == zombies[intY].getPos()) //checks for a collision
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