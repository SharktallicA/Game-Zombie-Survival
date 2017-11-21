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
	char charDirection = 0;
	bool boolAlive = true;
public:
	Entity() {};
	int getX();
	int getY();
	char getDirection() { return charDirection; };
	bool checkIfAlive() { return boolAlive; };
	virtual void move() {};
	void kill() { boolAlive = false; }
};

class Zombie : public Entity
{
private:
	int intID;
	int intDecay = 0;
	void changeDirection();
	bool checkMove(const coord, const char, const vector<Zombie>);
public:
	Zombie() : Entity() {};
	Zombie(int, coord);
	int getID() { return intID; };
	void move(const coord, const vector<Zombie>);
};

class Bullet : public Entity
{
public:
	Bullet() : Entity() {};
	Bullet(char, coord);
};

class Human : public Entity
{
private:
	string strName;
	void checkMove(const coord, const char);
	Bullet fire();
public:
	Human() : Entity() {};
	Human(string, coord);
	string getName() { return strName; };
	void move(const coord, vector<Bullet>);
};