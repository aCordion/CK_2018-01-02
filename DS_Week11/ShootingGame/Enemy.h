#pragma once
#include "GameObject.h"


class CEnemy : public CGameObject
{
	int count;
	bool dir;
public:
	CEnemy();
	~CEnemy();
	CEnemy(int x, int y, char *img) : CGameObject(x, y, img) { count = 0, dir = 0; }
	void update();
};

