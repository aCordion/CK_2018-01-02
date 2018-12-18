#include "Character.h"
#include <conio.h>
//enum DIR { RIGHT, UP, LEFT, DOWN};

Character::Character(char *c = "¢Æ",int h = 0, int b = 0, int nx = 1, int ny = 1, int cD = RIGHT) : img(c), iHP(h), iBullet(b), x(nx), y(ny), curDir(cD)
{
}


Character::~Character()
{
}

#include "GameManager.h"
enum DIR { Right, Up, Left, Down};
Player::Player(char * c, int h, int b, int nx, int ny, int cD) : Character(c, h, b, nx, ny, cD), img(c), iHP(h), iBullet(b), x(nx), y(ny), curDir(cD) {
	bGun = false;
}
void Player::setImg(int dir)
{
	switch (dir) {
	case Right:
		img = "¡æ";
		break;
	case Up:
		img = "¡è";
		break;
	case Left:
		img = "¡ç";
		break;
	case Down:
		img = "¡é";
		break;
	}
	curDir = dir;
}

enum typeEnum { AMMO, HEART, KEY, GUN, BULLET };
void Player::getItem(int iType)
{
	switch (iType) {
	case AMMO:
		iBullet += 5;
		break;
	case HEART:
		iHP += 1;
		break;
	case GUN:
		bGun = true;
		break;
	case BULLET:
		iHP--;
		break;
	}
}

void Player::gunShoot()
{
	if (bGun && (iBullet > 0)) {
		Bullet *inBullet = new Bullet("¢Á", x, y, 1, curDir, true);
		GameManager::getInstance()->getBList()->pushFront(inBullet);
		iBullet--;
	}
}

Enemy::Enemy(char * c, int h, int b, int nx, int ny, int cD) : Character(c, h, b, nx, ny, cD), img(c), iHP(h), iBullet(b), x(nx), y(ny), curDir(cD)
{
	switch (cD) {
	case Right:
		img = "¢º";
		break;
	case Up:
		img = "¡ã";
		break;
	case Left:
		img = "¢¸";
		break;
	case Down:
		img = "¡å";
		break;
	}
}


void Enemy::gunShoot()
{
	Bullet *inBullet = new Bullet("¢Á", x, y, 1, curDir, false);
	GameManager::getInstance()->getBList()->pushFront(inBullet);
}
