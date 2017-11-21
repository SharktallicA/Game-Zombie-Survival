#include "Entity.h"

int Entity::getX()
{
	return intX;
}
int Entity::getY()
{
	return intY;
}

Zombie::Zombie(int intNewID, coord coordNewPosition)
{
	intID = intNewID;
	intX = coordNewPosition.X;
	intY = coordNewPosition.Y;
	changeDirection(); //randomises the zombie's path
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
bool Zombie::checkMove(const coord coordBoard, const char charValue, const vector<Zombie> zombies)
{
	if ((charValue == 'W' || charValue == 'w') && intY > 1) return true;
	else if ((charValue == 'S' || charValue == 's') && intY < coordBoard.Y) return true;
	else if ((charValue == 'A' || charValue == 'a') && intX > 1) return true;
	else if ((charValue == 'D' || charValue == 'd') && intX < coordBoard.X) return true;
	else return false;
}

Human::Human(string strNewName, coord coordNewPosition)
{
	strName = strNewName;
	intX = coordNewPosition.X;
	intY = coordNewPosition.Y;
};

void Human::move(const coord coordBoard, vector<Bullet> bullets)
{
	//VIRTUAL KEYCODE REFERENCE: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	if (GetAsyncKeyState(0x57)) checkMove(coordBoard, charDirection = 'W'); //W was hit
	else if (GetAsyncKeyState(0x41)) checkMove(coordBoard, charDirection = 'A'); //A was hit
	else if (GetAsyncKeyState(0x53)) checkMove(coordBoard, charDirection = 'S'); //S was hit
	else if (GetAsyncKeyState(0x44)) checkMove(coordBoard, charDirection = 'D'); //D was hit
	else if (GetAsyncKeyState(VK_SPACE)) bullets.push_back(fire()); //space was hit
}
void Human::checkMove(const coord coordBoard, const char charValue)
{
	if ((charValue == 'W') && intY > 1) intY--;
	else if ((charValue == 'S') && intY < coordBoard.Y) intY++;
	else if ((charValue == 'A') && intX > 1) intX--;
	else if ((charValue == 'D') && intX < coordBoard.X) intX++;
}
Bullet Human::fire()
{
	return Bullet();
}

Bullet::Bullet(char charPath, coord coordNewPosition)
{
	charDirection = charPath;
	intX = coordNewPosition.X;
	intY = coordNewPosition.Y;
}