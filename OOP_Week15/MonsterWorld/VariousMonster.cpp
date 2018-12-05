#include "VariousMonster.h"

void Vampire::move(int** map, int maxx, int maxy) {
	if (!isSleep()) {
		int dir = rand() % 4;
		if (dir == 0) p[0]--;
		else if (dir == 1) p[0]++;
		else if (dir == 2) p[1]--;
		else p[1]++;
		clip(maxx, maxy);
		eat(map);
	}
}

void KGhost::move(int** map, int maxx, int maxy) {
	if (!isSleep()) {
		p = Point(rand() % maxx, rand() % maxy);
		clip(maxx, maxy);
		eat(map);
	}
}

void Jiangshi::move(int** map, int maxx, int maxy) {
	if (!isSleep()) {
		int dir = rand() % 2;
		int jump = rand() % 5 + 1;      // 2 -> 5
		if (bHori) p[0] += ((dir == 0) ? -jump : jump);
		else p[1] += ((dir == 0) ? -jump : jump);
		clip(maxx, maxy);
		eat(map);
	}
}

void Smombi::move(int ** map, int maxx, int maxy)
{
	if (!isSleep()) {
		int dir = rand() % 4;

		switch (dir) {
		case 0: p[0]++; p[1]++; break;
		case 1:	p[0]++; p[1]--; break;
		case 2:	p[0]--; p[1]--; break;
		case 3: p[0]--; p[1]++; break;
		}

		clip(maxx, maxy);
		eat(map);
	}
}

void SuperSmombi::move(int ** map, int maxx, int maxy)
{
	if (!isSleep()) {
		int dir = rand() % 4;
		int jump = (rand() % 5) + 1;

		switch (dir) {
		case 0: p[0] += jump; p[1] += jump; break;
		case 1: p[0] += jump; p[1] -= jump; break;
		case 2:	p[0] -= jump; p[1] -= jump; break;
		case 3: p[0] -= jump; p[1] += jump; break;
		}

		clip(maxx, maxy);
		eat(map);
	}
}
