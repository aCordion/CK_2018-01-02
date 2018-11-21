#include "GameMap.h"
#include "SnakeGameManager.h"
#include "ObjectList.h"
#include "Snake.h"
#include "Tail.h"
#include "util.h"
#include <conio.h>
#include <time.h>
#include <Windows.h>

void main() {
	CGameMap *gameMap = new CGameMap(25,25);
	//snake tail list
	CObjectList *tailList = new CObjectList;
	CGameObject *snakeHead = new CTail(10, 10);
	tailList->pushFront(snakeHead);

	//snake
	CSnake *snake = new CSnake(tailList);

	CSnakeGameManager::getInstance()->init(gameMap, snake);

	time_t curTime, oldTime = clock();
	ScreenInit();
	bool isContinue = true;

	//game logic
	while (isContinue) {
		CSnakeGameManager::getInstance()->updateGame();

		ScreenClear();
		CSnakeGameManager::getInstance()->draw();
		ScreenFlipping();

		if (CSnakeGameManager::getInstance()->isGameOver()) {
			isContinue = false;
		}
		while (true) {
			curTime = clock();
			if (curTime - oldTime > 33) {
				curTime = oldTime;
				break;
			}
		}
		
	}
	Sleep(1500);
}