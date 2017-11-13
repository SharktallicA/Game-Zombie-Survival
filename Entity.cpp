#include "Entity.h"

int Entity::getX()
{
	return intX;
}
int Entity::getY()
{
	return intY;
}
void Entity::setX(int intNewX)
{
	intX = intNewX;
}
void Entity::setY(int intNewY)
{
	intY = intNewY;
}

string Human::getName()
{
	return strName;
}