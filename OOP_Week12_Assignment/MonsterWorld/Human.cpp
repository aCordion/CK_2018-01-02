#include "Human.h"

//enum Direction {LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80};

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

void Tuman::moveHuman(int ** map, int maxx, int maxy, char ch)
{
	if (isLeft) {
		if (ch == KEY_A || ch == KEY_a) { x--; }
		else if (ch == KEY_D || ch == KEY_d) { x++; }
		else if (ch == KEY_W || ch == KEY_w) { y--; }
		else if (ch == KEY_S || ch == KEY_s) { y++; }
		else { return; }
	}
	else {
		if (ch == LEFT) { x--; }
		else if (ch == RIGHT) { x++; }
		else if (ch == UP) { y--; }
		else if (ch == DOWN) { y++; }
		else { return; }
	}

	clip(maxx, maxy);
	eat(map);
}
