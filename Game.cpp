#include "Game.h"

Game::Game()
{
	Utility::setColour(WHITE, BLACK);
}
bool Game::run()
{
	//purpose: handles game's operation
	//how to use: inside a while loop (e.g. while(game.run());) to allow continous play

	//set up game
	getDifficulty();
	createHuman();
	createZombies();

	//set up window
	Utility::setWindowTitle("Zombie Survival");
	if (boolIsExpert)
		Utility::setWindowSize(830, 800);
	else
		Utility::setWindowSize(595, 800);

	//run game loop
	printBoard();
	while (player.checkIfAlive())
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
	
	boolIsExpert = Utility::getYesNo("Use expert difficulty (y/n)? ");
	if (boolIsExpert)
		board = coord(90, 30);
	else
		board = coord(60, 30);
}
void Game::createZombies()
{
	//purpose: generates a bunch of zombies (based on difficulty) and randomises their location

	int intToMake = 10; //base zombie amount for normal difficulty
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
		zombies.push_back(Zombie(intIndex, intX, intY));
	}
}

void Game::printBoard()
{
	//purpose: prints out board with all entity starting positions in place
	
	//draw move counter
	Utility::clearScreen();
	Utility::setColour(WHITE, BLACK);
	cout << "Move " << intMove;

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
	Utility::setColour(YELLOW, BLACK);
	Utility::moveCursor(4 + player.getX(), 3 + player.getY());
	cout << charHUMAN;

	//draw zombies
	Utility::setColour(LIGHT_RED, BLACK);
	for (auto zombie : zombies)
	{
		Utility::moveCursor(4 + zombie.getX(), 3 + zombie.getY());
		cout << charZOMBIE;
	}

	//draw event board
	Utility::setColour(WHITE, BLACK);
	Utility::moveCursor(0, 37);
	cout << "Events: ";
}

void Game::update()
{
	//purpose: moves game forward in every turn; handles movement and redrawing

	//update human position
	coord playerLast;
	playerLast.X = player.getX();
	playerLast.Y = player.getY();
	player.move(board, zombies);

	//update zombie positions
	vector<coord> zombiesLast;
	for (unsigned int intIndex = 0; intIndex < zombies.size(); intIndex++)
	{
		coord zombieLast;
		zombieLast.X = zombies[intIndex].getX();
		zombieLast.Y = zombies[intIndex].getY();
		zombiesLast.push_back(zombieLast);
		zombies[intIndex].move(board, zombies);
	}

	//redraw move counter
	Utility::moveCursor(0, 0);
	Utility::setColour(WHITE, BLACK);
	cout << "Move " << intMove;

	//redraw human
	Utility::setColour(YELLOW, BLACK);
	Utility::moveCursor(4 + playerLast.X, 3 + playerLast.Y);
	cout << " ";
	Utility::moveCursor(4 + player.getX(), 3 + player.getY());
	cout << charHUMAN;

	//redraw zombies
	Utility::setColour(LIGHT_RED, BLACK);
	for (unsigned int intIndex = 0; intIndex < zombies.size(); intIndex++)
	{
		if (zombies[intIndex].checkIfAlive())
		{
			Utility::moveCursor(4 + zombiesLast[intIndex].X, 3 + zombiesLast[intIndex].Y);
			cout << " ";
			Utility::moveCursor(4 + zombies[intIndex].getX(), 3 + zombies[intIndex].getY());
			cout << charZOMBIE;
		}
	}

	//post-update procedures
	events(); 
	intMove++;
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
			if (zombies[intX].checkIfAlive() && zombies[intY].checkIfAlive() && zombies[intX].getID() != zombies[intY].getID() && zombies[intX].getX() == zombies[intY].getX() && zombies[intX].getY() == zombies[intY].getY()) //checks for a collision
			{
				zombies[intX].kill();
				zombies[intY].kill();
				coordDeaths.push_back(coord(zombies[intX].getX(), zombies[intX].getY()));
				cout << "Move " << intMove << ": zombies " << zombies[intX].getID() << " and " << zombies[intY].getID() << " have died due to a collision at " << zombies[intX].getX() << "x" << zombies[intX].getY() << "!" << endl;
			}
		}
	}
	return coordDeaths;
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