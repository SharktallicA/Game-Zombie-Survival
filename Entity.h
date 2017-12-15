#pragma once
#include "coord.h"
#include "Utility.h"
#include <conio.h>
#include <string>
#include <typeinfo>

using namespace std;

class Entity
{
protected:
	int intID;
	coord position;
	char charDirection = 0;
	bool boolAlive = true;
public:
	Entity() {};
	int getID() { return intID; };
	coord getPos() { return position; };
	char getDirection() { return charDirection; };
	bool checkIfAlive() { return boolAlive; };
	virtual void move() {};
	void kill() { boolAlive = false; }
};

class Human : public Entity
{
private:
	string strName;
	void checkMove(const coord, const char);
public:
	Human() : Entity() {};
	Human(string, coord);
	string getName() { return strName; };
	void move(const coord);
};

class Manhole : public Entity
{
public:
	Manhole() : Entity() {};
	Manhole(int, coord);
};

class Zombie : public Entity
{
private:
	int intDecay = 0;
	void changeDirection();
	bool checkMove(const coord, const char);
	bool homeIn(Human);
public:
	Zombie() : Entity() {};
	Zombie(int, coord);
	void move(const coord, Human);
};