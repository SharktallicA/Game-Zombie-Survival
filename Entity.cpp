#include "Entity.h"

Zombie::Zombie(int intNewID, coord coordNewPosition)
{
	intID = intNewID;
	position = coordNewPosition;
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
	if ((charValue == 'W' || charValue == 'w') && position.Y > 1) return true;
	else if ((charValue == 'S' || charValue == 's') && position.Y < coordBoard.Y) return true;
	else if ((charValue == 'A' || charValue == 'a') && position.X > 1) return true;
	else if ((charValue == 'D' || charValue == 'd') && position.X < coordBoard.X) return true;
	else return false;
}

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