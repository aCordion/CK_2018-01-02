#include "Bullet.h"


enum DIR { Right, Up, Left, Down };

Bullet::Bullet(char* i, int nx, int ny, int d, int dir, bool isP) : img(i), x(nx), y(ny), curDir(dir), isPlayers(isP), dmg(d)
{
}

void Bullet::move()
{
	switch (curDir) {
	case Right:
		x++;
		break;
	case Up:
		y--;
		break;
	case Left:
		x--;
		break;
	case Down:
		y++;
		break;
	}
}

void Bullet::draw()
{
	ScreenPrint(x * 2, y, img);
}