#pragma once
#include "GameMap.h"
#include "Character.h"
#include "ObjectList.h"
#include "BulletList.h"
#include "EnemyList.h"
#include "Bullet.h"
#include <time.h>
#include <conio.h>

class GameManager
{
	CGameMap m_map;
	Player m_player;
	CObjectList m_ItemList;
	BulletList *m_BulletList;
	EnemyList m_EnemyList;
	bool bDoorTriggered, keepPlay, isClear;
	int targetHP;

	GameManager();

public:
	static GameManager *getInstance();
	~GameManager();
	BulletList *getBList() { return m_BulletList; }
	void play();
	void fpMove();
	void fEShoot();
	void fColCheck();
	void init();
	void fInterface();
	void update();
	void draw();
};

