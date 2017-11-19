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
	int intX;
	int intY;
	bool boolAlive = true;
public:
	Entity() {};
	int getX();
	int getY();
	bool checkIfAlive() { return boolAlive; };
	virtual void move() {};
	void kill() { boolAlive = false; }
};

class Zombie : public Entity
{
private:
	int intID;
	int intDecay = 0;
	char charDirection = 0;
	void changeDirection();
	bool checkMove(const coord, const char, const vector<Zombie>);
public:
	Zombie() : Entity() {};
	Zombie(int, int, int);
	int getID() { return intID; };
	void move(const coord, const vector<Zombie>);
};

class Human : public Entity
{
private:
	string strName;
	bool checkMove(const coord, const char);
public:
	Human() : Entity() {};
	Human(string, int, int);
	string getName() { return strName; };
	void move(const coord, const vector<Zombie>);
};