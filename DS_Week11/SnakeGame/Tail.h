#pragma once
#include "GameObject.h"

class CTail : public CGameObject
{

public:
	~CTail();
	CTail(int x, int y) : CGameObject(x, y) { }

	void draw();
	void update() { }
};

