#include "Enemy.h"



CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}

void CEnemy::update()
{
//	static int count = 0;
//	static bool dir = 0;
	if (count == 5) {
		count = 0;
		dir = !dir;
	}
	int x = getX();
	int y = getY();
	if (dir) {
		x--;
	}
	else {
		x++;
	}
	setXY(x, y);
	count++;
}
