#include "MyCursor.h"
#include "util.h"


CMyCursor::CMyCursor() : m_x(0), m_y(0), m_width(80), m_height(25)
{
}


CMyCursor::~CMyCursor()
{
}

void CMyCursor::draw()
{
	char *cursorImg = "¢Ã";
	ScreenPrint(m_x * 2, m_y, cursorImg);
}
