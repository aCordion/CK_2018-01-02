#pragma once
#include "GameMap.h"
#include "ObjectList.h"
#include "Plane.h"

class CGameManager
{
	CGameMap *m_gameMap;
	CPlane * m_plane;
	CObjectList *m_bulletList;
	CGameManager();

public:
	~CGameManager();
	// singleton °´Ã¼ Á¢±Ù
	static CGameManager *getInstance();
	// initialise objects
	void init(CPlane*p, CGameMap*map, CObjectList *list);

	CPlane *getPlane() { return m_plane; }
	CGameMap *getMap() { return m_gameMap; }
	CObjectList *getBulletList() { return m_bulletList; }

	void checkCollison();

	void updateGame();
	void draw();
};
