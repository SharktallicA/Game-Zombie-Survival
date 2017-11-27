#pragma once

struct coord
{
	int X;
	int Y;
	coord() {};
	coord(int intNewX, int intNewY) { X = intNewX, Y = intNewY; };

	void operator=(const coord coordOther)
	{
		X = coordOther.X;
		Y = coordOther.Y;
	}

	bool operator==(const coord coordOther)
	{
		if (coordOther.X == X && coordOther.Y == Y) return true;
		else return false;
	}
};