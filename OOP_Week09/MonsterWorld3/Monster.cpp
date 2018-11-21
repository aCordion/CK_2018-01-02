#include "Monster.h"



void CMonster::clip(int maxx, int maxy)
{
	if (x < 0) x = 0;
	if (x >= maxx) x = maxx - 1;
	if (y < 0) y = 0;
	if (y >= maxy) y = maxy - 1;
}

//void CMonster::eat(int map[DIM][DIM])
void CMonster::eat(int** map)
{
	if (map[y][x] == 1) {
		map[y][x] = 0;
		nItem++;
		nEnergy += ITEM_ENERGY;
	}
	else { 
		if (nEnergy > 0) {
			nEnergy--;
		}
	}
}

//void CMonster::move(int map[DIM][DIM], int maxx, int maxy)
void CMonster::move(int** map, int maxx, int maxy)
{
	switch (rand() % 8) {
	case 0: y--; break;
	case 1: x++; y--; break;
	case 2: x++; break;
	case 3: x++; y++; break;
	case 4: y++; break;
	case 5: x--; y++; break;
	case 6: x--; break;
	case 7: x--; y--; break;
	}
	clip(maxx, maxy);
	eat(map);
}
