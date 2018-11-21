#include "GameManager.h"



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

void CGameManager::init(CPlane * p, CGameMap * map, CObjectList * list)
{
	m_plane = p;
	m_gameMap = map;
	m_bulletList = list;
}

#include "Bullet.h"
void CGameManager::checkCollison()
{
	// ¸Ê°úÀÇ Ãæµ¹
	// bi : bullet list index
	int count = m_bulletList->getCount();

	for (int bi = 0; bi < count; bi++) {
		CGameObject *curBullet = m_bulletList->getObject(bi);
		if (curBullet->getY() < 0) {
			m_bulletList->remove(bi);
			break;
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
	checkCollison();
}

void CGameManager::draw()
{
	m_plane->draw();

	// bullet draw
	int bNum = m_bulletList->getCount();
	for (int i = 0; i < bNum; i++) {
		m_bulletList->getObject(i)->draw();
	}
}
