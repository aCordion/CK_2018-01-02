#pragma once
#include "GameObject.h"

class CPlane : public CGameObject
{
	

public:
	~CPlane();
	CPlane(int x, int y, char* img) : CGameObject(x, y, img) {}

	void update();
};

