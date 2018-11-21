#pragma once
#include "GameObject.h"

class CBullet : public CGameObject
{
	

public:
	~CBullet() { }
	CBullet(int x, int y, char*img) : CGameObject(x, y, img) {}

	void update() {
		int x = getX();
		int y = getY();
		y--;
		setXY(x, y);
	}
};

