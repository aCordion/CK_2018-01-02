#include "Plane.h"
#include "GameMap.h"
#include "ObjectList.h"
#include "GameManager.h"
#include "util.h"
#include <time.h>

void main() {
	CGameMap *gameMap = new CGameMap(20, 20);
	CPlane *plane = new CPlane(10, 19, "бу");
	CObjectList *bulletList = new CObjectList();

	CGameManager::getInstance()->init(plane, gameMap, bulletList);

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