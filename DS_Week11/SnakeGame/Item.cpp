#include "Item.h"
#include "util.h"


CItem::~CItem()
{
}

void CItem::draw()
{
	char *itemImg = "��";
	int x = getX();
	int y = getY();
	ScreenPrint(x * 2, y, itemImg);
}
