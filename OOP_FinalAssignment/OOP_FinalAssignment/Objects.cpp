#include "Objects.h"

enum typeEnum {AMMO, HEART, KEY, GUN, BULLET};
char* type[] = {"£À", "¢¾", "¡×", "¡þ", "¢Á"};

Objects::Objects(int t, int nx, int ny) : iType(t), x(nx), y(ny)
{
	img = type[t];
}

void Objects::draw()
{
	ScreenPrint(x * 2, y, img);
}

