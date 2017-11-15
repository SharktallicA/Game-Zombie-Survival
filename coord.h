#pragma once

struct coord
{
	int X;
	int Y;
	coord() {};
	coord(int intNewX, int intNewY) { X = intNewX, Y = intNewY; };
};