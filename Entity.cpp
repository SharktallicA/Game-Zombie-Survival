#include "Entity.h"

int Entity::getX()
{
	return intX;
}
int Entity::getY()
{
	return intY;
}


Zombie::Zombie(int intNewID, int intNewX, int intNewY)
{
	intID = intNewID;
	intX = intNewX;
	intY = intNewY;
	changeDirection();
};
void Zombie::move(const coord coordBoard, const vector<Zombie> zombies)
{
	if (boolAlive)
	{
		if (intDecay == 0)
			changeDirection();

		while (!checkMove(coordBoard, charDirection, zombies))
			changeDirection();
		switch (charDirection)
		{
		case 'W':
		case 'w':
			intY--;
			break;
		case 'A':
		case 'a':
			intX--;
			break;
		case 'S':
		case 's':
			intY++;
			break;
		case 'D':
		case 'd':
			intX++;
			break;
		}
		intDecay--;
	}
}
void Zombie::changeDirection()
{
	//purpose: changes the direction of the zombie randomly and generates a path decay

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
bool Zombie::checkMove(const coord coordBoard, const char charValue, const vector<Zombie> zombies)
{
	if ((charValue == 'W' || charValue == 'w') && intY > 1) return true;
	else if ((charValue == 'S' || charValue == 's') && intY < coordBoard.Y) return true;
	else if ((charValue == 'A' || charValue == 'a') && intX > 1) return true;
	else if ((charValue == 'D' || charValue == 'd') && intX < coordBoard.X) return true;
	else return false;
}

Human::Human(string strNewName, int intNewX, int intNewY)
{
	strName = strNewName;
	intX = intNewX;
	intY = intNewY;
};
void Human::move(const coord coordBoard, const vector<Zombie> zombies)
{
	char charInput = '0';

	while (!checkMove(coordBoard, charInput))
		charInput = Utility::getCharacter();
	
	switch (charInput)
	{
	case 'W':
	case 'w':
		intY--;
		break;
	case 'A':
	case 'a':
		intX--;
		break;
	case 'S':
	case 's':
		intY++;
		break;
	case 'D':
	case 'd':
		intX++;
		break;
	}
}
bool Human::checkMove(const coord coordBoard, const char charValue)
{
	if ((charValue == 'W' || charValue == 'w') && intY > 1) return true;
	else if ((charValue == 'S' || charValue == 's') && intY < coordBoard.Y) return true;
	else if ((charValue == 'A' || charValue == 'a') && intX > 1) return true;
	else if ((charValue == 'D' || charValue == 'd') && intX < coordBoard.X) return true;
	else return false;
}