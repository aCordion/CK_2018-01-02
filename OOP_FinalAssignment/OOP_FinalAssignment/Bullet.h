#pragma once
#include "util.h"

class Bullet
{
	char *img;
	int x, y;
	bool isPlayers;
	int curDir;
	int dmg;

public:
	Bullet(char * i = "¢Á", int nx = 1, int ny = 1, int d = 1, int dir = 0, bool isP = false);
	~Bullet() {}

	int getX() { return x; }
	int getY() { return y; }
	int getDmg() { return dmg; }

	void setX(int nx) { x = nx; }
	void setY(int ny) { y = ny; }
	void setXY(int nx, int ny) { x = nx; y = ny; }
	void setImg(char*i) { img = i; }

	void draw();
	bool getPBullet() { return isPlayers; }
	void move();
};
