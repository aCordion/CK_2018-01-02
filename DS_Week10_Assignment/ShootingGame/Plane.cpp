#include "Plane.h"
#include "util.h"	//Ű���� ���� ��� ���
#include "GameManager.h"

#include <conio.h>

CPlane::~CPlane()
{
}

void CPlane::update()
{
	if (_kbhit()) {
		int nKey = _getch();
		int planeX = getX();
		int planeY = getY();
		switch (nKey) {
		case LEFT:
			planeX--;
			break;
		case RIGHT:
			planeX++;
			break;
		case SPACE:
			CGameObject bullet(planeX, planeY, "��");
			CGameManager::getInstance()->getBulletList()->pushFront(bullet);
			break;
		}
		int mapWidth = CGameManager::getInstance()->getMap()->getWidth();
		if (planeX >= 1 && planeX < mapWidth -1) {
			setXY(planeX, planeY);
		}
	}
}
