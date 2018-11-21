#include "VariousMonsters.h"

void Vampire::move(int ** map, int maxx, int maxy)
{
	int dir = rand() % 4;
	if (dir == 0) x--;
	else if (dir == 1) x++;
	else if (dir == 2) y--;
	else y++;
	clip(maxx, maxy);
	eat(map);
}

void KGhost::move(int ** map, int maxx, int maxy)
{
	x = rand() % maxx;
	y = rand() % maxy;
	clip(maxx, maxy);
	eat(map);
}

void Jiangshi::move(int ** map, int maxx, int maxy)
{
	int dir = rand() % 2;
	int jump = rand() % 5 + 1;
	if (bHori) x += ((dir == 0) ? -jump : jump);
	else y += ((dir == 0) ? -jump : jump);
	clip(maxx, maxy);
	eat(map);
}
