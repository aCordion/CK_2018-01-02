#pragma once
#include "GameObject.h"

class CItem : public CGameObject
{
public:
	~CItem();
	CItem(int x, int y) : CGameObject(x, y) {}

	void draw();
	void update() { }
};

