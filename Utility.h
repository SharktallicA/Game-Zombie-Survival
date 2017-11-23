#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <windows.h>
#include <conio.h>

using namespace std;

enum COLOUR
{
	BLACK, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, DEFAULT, GRAY, LIGHT_BLUE,
	LIGHT_GREEN, LIGHT_AQUA, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, WHITE
};

class Utility
{
	//purpose: provides program-wide methods for common functions

private:
	Utility() {}; //prevents class from being constructed
	~Utility() {};
public:
	static bool getYesNo();
	static bool getYesNo(string);
	static string getString();
	static string getString(string);
	static int getInteger();
	static int getInteger(string, int, int);

	static int generateNumber(int, int);

	static void clearScreen();
	static void setWindowTitle(string);
	static void setWindowSize(unsigned int, unsigned int);
	static void setColour(COLOUR, COLOUR);
	static void moveCursor(SHORT, SHORT);
};