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
	char charDirection = 0;
	void changeDirection();
	bool checkMove(const coord, const char, const vector<Zombie>);
public:
	Zombie() : Entity() {};
	Zombie(int, int);
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
	string getName();
	void move(const coord, const vector<Zombie>);
};