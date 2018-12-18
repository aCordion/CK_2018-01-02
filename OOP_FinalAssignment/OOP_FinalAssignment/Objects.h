#pragma once
#include "util.h"
// type 0 = Ammo, 1 = healthUp, 2 = Key
class Objects
{
protected:
	int x, y;
	int iType;
	char *img;

public:
	Objects(int t = 0, int nx = 0, int ny = 0);
	~Objects() {}

	int getX() { return x; }
	int getY() { return y; }
	int getType() { return iType; }

	void setX(int nx) { x = nx; }
	void setY(int ny) { y = ny; }
	void setXY(int nx, int ny) { x = nx; y = ny; }

	void draw();
};


