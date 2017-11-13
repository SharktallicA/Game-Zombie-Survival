#pragma once
#include "Utility.h"
#include <string>

using namespace std;

class Entity
{
private:
	int intX;
	int intY;
public:
	Entity() {};

	int getX();
	int getY();
	void setX(int);
	void setY(int);
};

class Human : public Entity
{
private:
	string strName;
public:
	Human() : Entity() {};
	Human(string strNewName) { strName = strNewName; };

	string getName();
};

class Zombie : public Entity
{

};