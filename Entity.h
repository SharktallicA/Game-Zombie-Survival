#pragma once
#include "Utility.h"
#include <string>
#include <conio.h>

using namespace std;

class Entity
{
protected:
	int intX;
	int intY;
public:
	Entity() {};
	int getX();
	int getY();
	virtual void move() {};
};

class Human : public Entity
{
private:
	string strName;
public:
	Human() : Entity() {};
	Human(string, int, int);
	string getName();
	void move();
};

class Zombie : public Entity
{
public:
	Zombie() : Entity() {};
	Zombie(int, int);
	void move();
};