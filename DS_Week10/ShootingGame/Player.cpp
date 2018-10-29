#include "Player.h"
#include "util.h"


CPlayer::CPlayer() : m_x(0), m_y(0), m_width(80), m_height(25)
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::draw()
{
	char *playerImg = "¡Ê";	//¥Ä
	ScreenPrint(m_x * 2, m_y, playerImg);
}
