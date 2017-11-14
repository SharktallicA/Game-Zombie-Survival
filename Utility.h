#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <windows.h>

using namespace std;

class Utility
{
	//purpose: provides program-wide methods for common functions

private:
	Utility() {}; //private to prevent class from being constructed
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
	static void moveCursor(unsigned int, unsigned int);
};