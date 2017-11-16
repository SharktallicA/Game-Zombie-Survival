#include "Entity.h"

int Entity::getX()
{
	return intX;
}
int Entity::getY()
{
	return intY;
}

Human::Human(string strNewName, int intNewX, int intNewY)
{
	strName = strNewName;
	intX = intNewX;
	intY = intNewY;
};
string Human::getName()
{
	return strName;
}
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

Zombie::Zombie(int intNewX, int intNewY)
{
	intX = intNewX;
	intY = intNewY;
};
void Zombie::move(const coord coordBoard)
{
	if (intDecay == 0)
		intDecay = Utility::generateNumber(1, 5);
	else
	{
		intDecay--;
	}

	if (intInput == 1)
		intX++;
	else if (intInput == 2)
		intX--;
	else if (intInput == 3)
		intY++;
	else if (intInput == 4)
		intY--;
}