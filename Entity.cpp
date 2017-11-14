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
void Human::move()
{
	char charInput = 0; //variable for input character
	bool boolMoveLegal = false; //flag to indicate if move is valid

	while (!boolMoveLegal) //iterate until valid move
	{
		charInput = _getch(); //gets character (method will need to be replaced with something that is not from the MS-DOS days...)
		switch (charInput)
		{
		case 'W':
		case 'w':
			break;
		case 'A':
		case 'a':
			break;
		case 's':
		case 'S':
			break;
		case 'D':
		case 'd':
			break;
		}
	}
}

Zombie::Zombie(int intNewX, int intNewY)
{
	intX = intNewX;
	intY = intNewY;
};
void Zombie::move()
{

}