#include "Monster.h"

void Monster::clip(int maxx, int maxy) {
	if (x < 0) x = 0;
	if (x >= maxx) x = maxx - 1;
	if (y < 0) y = 0;
	if (y >= maxy) y = maxy - 1;
}
void Monster::eat(int** map) {
	if (map[y][x] == 1) {
		map[y][x] = 0;
		nItem++;
		nEnergy += ITEM_ENERGY;
	}
	else {
		if(nEnergy > 0) nEnergy--;
	}
}
 
void Monster::draw(Canvas &canvas) { canvas.draw(x, y, icon); }
void Monster::move(int** map, int maxx, int maxy) {
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

void Monster::
print() { cout << "\t" << name << icon << ":" << nItem << " ¿¡³ÊÁö : " << nEnergy << endl; }