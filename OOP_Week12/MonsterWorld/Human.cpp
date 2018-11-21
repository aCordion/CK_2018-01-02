#include "Human.h"

enum Direction {LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80};

void Human::move(int ** map, int maxx, int maxy)
{
	if (_kbhit()) {
		char ch = getDirKey();
		if (ch == LEFT) { x--; }
		else if (ch == RIGHT) { x++; }
		else if (ch == UP) { y--; }
		else if (ch == DOWN) { y++; }
		else { return; }

		clip(maxx, maxy);
		eat(map);
	}
}
