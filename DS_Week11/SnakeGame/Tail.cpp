#include "Tail.h"
#include "util.h"


CTail::~CTail()
{
}

void CTail::draw()
{
	char *tileImg = "¡Þ";
	int x = getX();
	int y = getY();
	ScreenPrint(x * 2, y, tileImg);
}
