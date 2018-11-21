#pragma once

class CGameMap;
class CSnake;
class CItem;

class CSnakeGameManager
{
	CGameMap *m_gameMap;
	CSnake *m_snake;
	CItem *m_item;
	bool m_isGameOver;

	CSnakeGameManager();

public:
	~CSnakeGameManager();
	//singleton °´Ã¼ Á¢±Ù
	static CSnakeGameManager *getInstance();
	//initialize objects
	void init(CGameMap *map, CSnake*snake);
	void itemSet();

	//getters
	CGameMap *getGameMap() { return m_gameMap; }
	CSnake *getSnake() { return m_snake; }
	bool isGameOver() { return m_isGameOver; }

	void checkCollision();

	void updateGame();
	void draw();
};

