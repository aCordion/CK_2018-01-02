#include "SnakeGameManager.h"
#include "Tail.h"
#include "Snake.h"
#include "Item.h"
#include "GameMap.h"
#include "ObjectList.h"
#include "util.h"
#include <Windows.h>
#include <conio.h>
#include <time.h>


CSnakeGameManager::CSnakeGameManager()
{
}


CSnakeGameManager::~CSnakeGameManager()
{
}

CSnakeGameManager * CSnakeGameManager::getInstance()
{
	static CSnakeGameManager instance;
	return &instance;
}

void CSnakeGameManager::init(CGameMap * map, CSnake * snake)
{
	m_gameMap = map;
	m_snake = snake;
	int width = m_gameMap->getWidth();
	int heigth = m_gameMap->getHeigth();
	//item의 생성 위치
	/*
	int x = (rand() % (width - 2)) + 1;
	int y = (rand() % (heigth - 2)) + 1;
	m_item = new CItem(x, y);
	*/
	itemSet();
	m_isGameOver = false;

}

void CSnakeGameManager::itemSet()
{
	int width = m_gameMap->getWidth();
	int heigth = m_gameMap->getHeigth();
	while (true) {
		int x = (rand() % (width - 2)) + 1;
		int y = (rand() % (heigth - 2)) + 1;
		if (getGameMap()->getMapdata(x, y) == 0) {
			m_item = new CItem(x, y);
			break;
		}
	}
}

void CSnakeGameManager::checkCollision()
{

	int x = m_snake->getTails()->getObject(0)->getX();
	int y = m_snake->getTails()->getObject(0)->getY();
	int width = m_gameMap->getWidth();
	int heigth = m_gameMap->getHeigth();
	int tCount = m_snake->getTails()->getCount();

	// to do #1 = snake head와 맵하고의 충돌
	if (x <= 0 || x > width - 2 || y <= 0 || y > heigth - 2) {
		m_isGameOver = true;
	}

	// to do #2 = snake head와 item 충돌
	//item 획득
	//item 삭제
	//tail 생성 ==> 리스트에 추가
	if ((x == m_item->getX()) && (y == m_item->getY())) {
		delete m_item;
		itemSet();
		tCount = m_snake->getTails()->getCount();
		int tX = m_snake->getTails()->getObject(tCount - 1)->getX();
		int tY = m_snake->getTails()->getObject(tCount - 1)->getY();

		CGameObject *tail = new CTail(tX,tY);
		CSnakeGameManager::getInstance()->getSnake()->getTails()->pushTail(tail);
	}

	// to do #3 = snake head와 몸통 충돌 처리
	//m_isGameOver = true;

	for (int i = 1; i < tCount; i++) {
		int tX = m_snake->getTails()->getObject(i)->getX();
		int tY = m_snake->getTails()->getObject(i)->getY();
		if (x == tX && y == tY) {
			m_isGameOver = true;
		}
	}
}

void CSnakeGameManager::updateGame()
{
	time_t curTime, oldTime = clock();
	while (true) {
		//snake's direction update
		if (_kbhit()) {
			int nKey = _getch();
			DIR dir = m_snake->getDir();
			int sCnt = m_snake->getTails()->getCount();
			if (nKey == LEFT || nKey == RIGHT || nKey == UP || nKey == DOWN) {
				if ((sCnt > 1) && (dir == RIGHT) && (nKey == LEFT)) {}
				else if ((sCnt > 1) && (dir == LEFT) && (nKey == RIGHT)) {}
				else if ((sCnt > 1) && (dir == UP) && (nKey == DOWN)) {}
				else if ((sCnt > 1) && (dir == DOWN) && (nKey == UP)) {}
				else { dir = nKey; }
			}
			m_snake->setDir(dir);
		}
		curTime = clock();
		if (curTime - oldTime > 33 * 4) {
			oldTime = curTime;
			break;
		}
	}
	m_snake->update();
	checkCollision();
}

void CSnakeGameManager::draw()
{
	//game map draw;
	m_gameMap->draw();

	//snake draw
	int sNum = m_snake->getTails()->getCount();
	for (int i = 0; i < sNum; i++) {
		m_snake->getTails()->getObject(i)->draw();
	}

	//item draw
	m_item->draw();

	if (m_isGameOver) {
		int x = m_gameMap->getWidth() / 2;
		int y = m_gameMap->getHeigth() / 2;
		ScreenPrint(x, y, "Game Over...!!!");
	}
}
