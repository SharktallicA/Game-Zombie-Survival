#include "Entity.h"

Human::Human(string strNewName, coord coordNewPosition)
{
	//purpose: Human class constructor
	//parametres: (strNewName) assigned name, (coordNewPosition) assigned starting position

	strName = strNewName;
	position = coordNewPosition;
};
void Human::move(const coord BOARD)
{
	//purpose: Human movement handler
	//parametres: (BOARD) game board size reference
	//keycodes: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	//check whether any of the WASD keys were hit:
	if (GetAsyncKeyState(0x57)) checkMove(BOARD, charDirection = 'W'); //W was hit
	else if (GetAsyncKeyState(0x41)) checkMove(BOARD, charDirection = 'A'); //A was hit
	else if (GetAsyncKeyState(0x53)) checkMove(BOARD, charDirection = 'S'); //S was hit
	else if (GetAsyncKeyState(0x44)) checkMove(BOARD, charDirection = 'D'); //D was hit
}
void Human::checkMove(const coord BOARD, const char VALUE)
{
	//purpose: checks whether the requested movement can be made (bounds checking)
	//parametres: (BOARD) game board size reference, (VALUE) character to indicate direction of movement

	if ((VALUE == 'W') && position.Y > 1) position.Y--;
	else if ((VALUE == 'S') && position.Y < BOARD.Y) position.Y++;
	else if ((VALUE == 'A') && position.X > 1) position.X--;
	else if ((VALUE == 'D') && position.X < BOARD.X) position.X++;
}

Manhole::Manhole(int intNewID, coord coordNewPosition)
{
	//purpose: Manhole class constructor
	//parametres: (intNewID) assigned ID, (coordNewPosition) assigned position

	intID = intNewID;
	position = coordNewPosition;
};

Zombie::Zombie(int intNewID, coord coordNewPosition)
{
	//purpose: Zombie class constructor
	//parametres: (intNewID) assigned ID, (coordNewPosition) assigned starting position

	intID = intNewID;
	intSight = 1;
	position = coordNewPosition;
	changeDirection(); //randomises the zombie's first path
};
void Zombie::move(const coord BOARD, Human PLAYER)
{
	//purpose: Zombie movement handler
	//parametres: (BOARD) game board size reference, (PLAYER) human character reference

	if (boolAlive) //check if zombie is alive before proceeding
	{
		int intXDist = PLAYER.getPos().X - position.X; //get distance between human X and zombie X
		int intYDist = PLAYER.getPos().Y - position.Y; //get distance between human Y and zombie Y

		if (intXDist >= (-intSight) && intXDist <= intSight) //check if zombie is in homing range of human on X-axis
		{
			moveHoming(PLAYER); //make human-homing zombie move (arguments: board size, human object)
		}
		else
		{
			if (intYDist >= (-intSight) && intYDist <= intSight) //check if zombie is in homing range of human on Y-axis
			{
				moveHoming(PLAYER); //make human-homing zombie move (arguments: board size, human object)
			}
			else
			{
				moveStatic(BOARD); //make static (random) zombie move (arguments: board size)
			}
		}
	}
}
void Zombie::changeDirection()
{
	//purpose: changes the direction of the zombie randomly and generates a path decay
	//pre-condition: only called if the path has decayed to zero

	intDecay = Utility::generateNumber(1, 10);
	int intDirection = Utility::generateNumber(1, 4);

	if (intDirection == 1)
		charDirection = 'W';
	else if (intDirection == 2)
		charDirection = 'S';
	else if (intDirection == 3)
		charDirection = 'A';
	else if (intDirection == 4)
		charDirection = 'D';
}
bool Zombie::checkMove(const coord BOARD, const char VALUE)
{
	//purpose: checks whether the requested movement can be made (bounds checking)
	//parametres: (BOARD) game board size reference, (VALUE) character to indicate direction of movement

	if ((VALUE == 'W') && position.Y > 1) return true;
	else if ((VALUE == 'S') && position.Y < BOARD.Y) return true;
	else if ((VALUE == 'A') && position.X > 1) return true;
	else if ((VALUE == 'D') && position.X < BOARD.X) return true;
	else return false;
}
void Zombie::moveStatic(const coord BOARD)
{
	//purpose: performs a normal movement via randomly-decided paths
	//parametres: (BOARD) game board size reference

	if (intDecay == 0) changeDirection();
	while (!checkMove(BOARD, charDirection)) changeDirection();

	switch (charDirection)
	{
	case 'W':
	case 'w':
		position.Y--;
		break;
	case 'A':
	case 'a':
		position.X--;
		break;
	case 'S':
	case 's':
		position.Y++;
		break;
	case 'D':
	case 'd':
		position.X++;
		break;
	}
	intDecay--;
}
void Zombie::moveHoming(Human PLAYER)
{
	//purpose: performs a homing-in movement with three distinct path types
	//parametres: (PLAYER) human character reference

	int intDirection = Utility::generateNumber(1, 3); //generate number for selecting direction type
	const int intMoveAmount = 1;  //variable for zombie move amount  (is a variable in case of later changes)

	if (intDirection == 1) //move on singular (X) axis
	{
		if (PLAYER.getPos().X < position.X)
		{
			position.X -= intMoveAmount;
		}
		else if (PLAYER.getPos().X > position.X)
		{
			position.X += intMoveAmount;
		}
	}
	else if (intDirection == 2) //move on singular (XY) axis
	{
		if (PLAYER.getPos().Y < position.Y)
		{
			position.Y -= intMoveAmount;
		}
		else if (PLAYER.getPos().Y > position.Y)
		{
			position.Y += intMoveAmount;
		}
	}
	else if (intDirection == 3) //move on multi (X and Y) axis
	{
		if (PLAYER.getPos().X < position.X)
		{
			position.X -= intMoveAmount;
		}
		else if (PLAYER.getPos().X > position.X)
		{
			position.X += intMoveAmount;
		}
		if (PLAYER.getPos().Y < position.Y)
		{
			position.Y -= intMoveAmount;
		}
		else if (PLAYER.getPos().Y > position.Y)
		{
			position.Y += intMoveAmount;
		}
	}
}