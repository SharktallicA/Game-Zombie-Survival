#include "Entity.h"

Human::Human(string strNewName, coord coordNewPosition)
{
	strName = strNewName;
	position = coordNewPosition;
};
void Human::move(const coord coordBoard)
{
	//VIRTUAL KEYCODE REFERENCE: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	if (GetAsyncKeyState(0x57)) checkMove(coordBoard, charDirection = 'W'); //W was hit
	else if (GetAsyncKeyState(0x41)) checkMove(coordBoard, charDirection = 'A'); //A was hit
	else if (GetAsyncKeyState(0x53)) checkMove(coordBoard, charDirection = 'S'); //S was hit
	else if (GetAsyncKeyState(0x44)) checkMove(coordBoard, charDirection = 'D'); //D was hit
}
void Human::checkMove(const coord coordBoard, const char charValue)
{
	if ((charValue == 'W') && position.Y > 1) position.Y--;
	else if ((charValue == 'S') && position.Y < coordBoard.Y) position.Y++;
	else if ((charValue == 'A') && position.X > 1) position.X--;
	else if ((charValue == 'D') && position.X < coordBoard.X) position.X++;
}

Manhole::Manhole(int intNewID, coord coordNewPosition)
{
	intID = intNewID;
	position = coordNewPosition;
};

Zombie::Zombie(int intNewID, coord coordNewPosition)
{
	intID = intNewID;
	position = coordNewPosition;
	changeDirection(); //randomises the zombie's path
};
void Zombie::move(const coord coordBoard, Human player)
{
	if (boolAlive)
	{
		if (intDecay == 0) changeDirection();
		while (!checkMove(coordBoard, charDirection)) changeDirection();

		if (!homeIn(player))
		{
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
	}
}
void Zombie::changeDirection()
{
	//purpose: changes the direction of the zombie randomly and generates a path decay
	//pre-condition: ideally only calleed if the path has decayed to zero

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
bool Zombie::checkMove(const coord coordBoard, const char charValue)
{
	if ((charValue == 'W' || charValue == 'w') && position.Y > 1) return true;
	else if ((charValue == 'S' || charValue == 's') && position.Y < coordBoard.Y) return true;
	else if ((charValue == 'A' || charValue == 'a') && position.X > 1) return true;
	else if ((charValue == 'D' || charValue == 'd') && position.X < coordBoard.X) return true;
	else return false;
}
bool Zombie::homeIn(Human player)
{
	return false;
	bool boolIsHoming = false;

	int intXDist = player.getPos().X - position.X;
	int intYDist = player.getPos().Y - position.Y;

	if (intXDist >= 0 || intXDist <= 4)
	{
		position.X++;
		boolIsHoming = true;
	}
	else if (intXDist >= -4 || intXDist <= -1)
	{
		position.X--;
		boolIsHoming = true;
	}

	if (intYDist >= 0 || intYDist <= 2)
	{
		position.Y++;
		boolIsHoming = true;
	}
	else if (intYDist >= 2 || intYDist <= -1)
	{
		position.Y--;
		boolIsHoming = true;
	}
	return boolIsHoming;
}