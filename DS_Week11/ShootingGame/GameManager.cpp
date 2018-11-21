#include "GameManager.h"
#include "Bullet.h"
#include "Enemy.h"

#define ENEMY_DELAY 50

CGameManager::CGameManager()
{
}


CGameManager::~CGameManager()
{
}

CGameManager * CGameManager::getInstance()
{
	static CGameManager instance;
	return &instance;
}

void CGameManager::init(CPlane * p, CGameMap * map, CObjectList * list, CObjectList * elist)
{
	m_plane = p;
	m_gameMap = map;
	m_bulletList = list;
	m_enemyList = elist;
}

#include "Bullet.h"
void CGameManager::checkCollison()
{
	// ¸Ê°úÀÇ Ãæµ¹
	// bi : bullet list index
	int count = m_bulletList->getCount();
	int eCount = m_enemyList->getCount();

	for (int bi = 0; bi < count; bi++) {
		CGameObject *curBullet = m_bulletList->getObject(bi);
		if (curBullet->getY() < 1) {
			m_bulletList->remove(bi);
			break;
		}
		for (int ei = 0; ei < eCount; ei++) {
			CGameObject *curEnemy = m_enemyList->getObject(ei);
			if ((curEnemy->getY() == curBullet->getY()) && (curEnemy->getX() == curBullet->getX())) {
				m_bulletList->remove(bi);
				m_enemyList->remove(ei);
				break;
			}
		}

	}
}

void CGameManager::updateGame()
{
	//plane update
	m_plane->update();

	// bullet update
	for (int i = 0; i < m_bulletList->getCount(); i++) {
		CBullet *curBullet = (CBullet*)m_bulletList->getObject(i);
		curBullet->update();
	}
	static int delayTime = 0;
	delayTime++;
	// enemy update	//
	if (delayTime >= ENEMY_DELAY) {
		delayTime = 0;
		for (int i = 0; i < m_enemyList->getCount(); i++) {
			CEnemy *curEnemy = (CEnemy*)m_enemyList->getObject(i);
			curEnemy->update();
		}
	}
	checkCollison();
}

void CGameManager::draw()
{
	m_gameMap->draw();
	m_plane->draw();

	// bullet draw
	int bNum = m_bulletList->getCount();
	for (int i = 0; i < bNum; i++) {
		m_bulletList->getObject(i)->draw();
	}

	// enemy draw
	int eNum = m_enemyList->getCount();
	for (int i = 0; i < eNum; i++) {
		m_enemyList->getObject(i)->draw();
	}
}
