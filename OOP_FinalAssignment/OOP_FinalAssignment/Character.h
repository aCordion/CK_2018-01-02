#pragma once
#include "util.h"
#include "Objects.h"
#include "Bullet.h"

class Character
{
protected:
	char* img;
	int iHP;
	int iBullet;
	int x, y, curDir;

public:
	Character(char *c, int h, int b, int nx, int ny, int cD);
	~Character();

	int getX() { return x; }
	int getY() { return y; }

	void setX(int nx) { x = nx; }
	void setY(int ny) { y = ny; }

	void draw() { ScreenPrint(x * 2, y, img); }
};

class Player : public Character {
	
	char* img;
	int iHP;
	int iBullet;
	int x, y, curDir;
	bool bGun;

public:
	Player(char *c = "¢Â", int h = 3, int b = 10, int nx = 2, int ny = 17, int cD = 0);

	void setXY(int nx, int ny) { x = nx; y = ny; }
	void setImg(int dir);
	int getX() { return x; }
	int getY() { return y; }
	int getHP() { return iHP; }

	void getItem(int iType);
	void getDmg(int dmg) { iHP -= dmg; }
	bool getBGun() { return bGun; }
	int getCurDir() { return curDir; }
	int getIBullet() { return iBullet; }
	void gunShoot();
	void draw() { ScreenPrint(x * 2, y, img); }
};

class Enemy : public Character {
	
	char* img;
	int iHP;
	int iBullet;
	int x, y, curDir;

public:
	Enemy(char *c = "¢É", int h = 3, int b = -1, int nx = 1, int ny = 1, int cD = 0);

	void gunShoot();
	int getX() { return x; }
	int getY() { return y; }
	int getHP() { return iHP; }

	void getDmg(int dmg) { iHP -= dmg; }
	void setXY(int nx, int ny) { x = nx; y = ny; }
	void draw() { ScreenPrint(x * 2, y, img); }
};