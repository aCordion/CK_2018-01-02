#include "GameObject.h"
#include "util.h"


CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
}

void CGameObject::draw()
{
	ScreenPrint(m_x * 2, m_y, m_img);
}
