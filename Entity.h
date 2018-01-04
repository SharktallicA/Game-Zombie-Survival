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
	Entity(void) {};
	int getID(void) { return intID; };
	coord getPos(void) { return position; };
	char getDirection(void) { return charDirection; };
	bool checkIfAlive(void) { return boolAlive; };
	virtual void move(void) {};
	void kill(void) { boolAlive = false; }
};

class Human : public Entity
{
private:
	string strName;
	void checkMove(const coord, const char);
public:
	Human() : Entity() {};
	Human(string, coord);
	string getName(void) { return strName; };
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
	int intSight = 0;
	void changeDirection(void);
	bool checkMove(const coord, const char);
	void moveStatic(const coord);
	void moveHoming(Human);
public:
	Zombie() : Entity() {};
	Zombie(int, int, coord);
	void move(const coord, Human);
};