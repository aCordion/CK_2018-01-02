#include "Plane.h"
#include "GameMap.h"
#include "ObjectList.h"
#include "GameManager.h"
#include "Enemy.h"
#include "util.h"
#include <time.h>

void main() {
	CGameMap *gameMap = new CGameMap(20, 20);
	CPlane *plane = new CPlane(10, gameMap->getHeigth()-2, "бу");
	CObjectList *bulletList = new CObjectList();
	CObjectList *enemyList = new CObjectList();

	for (int i = 0; i < 5; i++) {
		int x = (i * 2) + 5;
		CGameObject *enemy = new CEnemy(x, 2, "б┌");
		enemyList->pushTail(enemy);//
	}

	CGameManager::getInstance()->init(plane, gameMap, bulletList, enemyList);

	int curTime, oldTime;
	oldTime = clock();
	ScreenInit();
	bool isContinue = true;
	while (isContinue) {
		ScreenClear();
		CGameManager::getInstance()->draw();
		ScreenFlipping();

		CGameManager::getInstance()->updateGame();
		while (true) {
			curTime = clock();
			if (curTime - oldTime > 33) {
				oldTime = curTime;
				break;
			}
		}
	}
	ScreenRelease();
}