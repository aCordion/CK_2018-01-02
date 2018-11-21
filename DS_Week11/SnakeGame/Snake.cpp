#include "Snake.h"
#include "ObjectList.h"
#include "util.h"


CSnake::~CSnake()
{
}

CSnake::CSnake(CObjectList * list) : m_tailList(list), m_dir(DOWN)
{
}

void CSnake::update()
{
	int headX = m_tailList->getObject(0)->getX();
	int headY = m_tailList->getObject(0)->getY();

	int sCnt = m_tailList->getCount();

	switch (m_dir) {
	case LEFT:
		headX--;
		break;
	case RIGHT:
		headX++;
		break;
	case UP:
		headY--;
		break;
	case DOWN:
		headY++;
		break;
	}
	int tailCount = m_tailList->getCount();
	// ²¿¸® ÁÂÇ¥ update
	for (int i = tailCount - 1; i >= 1; i--) {
		int newX = m_tailList->getObject(i - 1)->getX();
		int newY = m_tailList->getObject(i - 1)->getY();
		m_tailList->getObject(i)->setXY(newX, newY);
	}
	// ¸Ó¸® ÁÂÇ¥ update

	m_tailList->getObject(0)->setXY(headX, headY);

}

void CSnake::draw()
{
	int count = m_tailList->getCount();
	for (int i = 0; i < count; i++) {
		m_tailList->getObject(i)->draw();
	}
}
