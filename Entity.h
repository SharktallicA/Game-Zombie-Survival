#pragma once
#include "coord.h"
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

class Zombie : public Entity
{
private:
	int intDecay = 0;
	char charDirect
public:
	Zombie() : Entity() {};
	Zombie(int, int);
	void move(const coord);
};

class Human : public Entity
{
private:
	string strName;
	bool checkMove(const coord, const char);
public:
	Human() : Entity() {};
	Human(string, int, int);
	string getName();
	void move(const coord, const vector<Zombie>);
};