#include "Human.h"


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

	if (ch == KEY_A || ch == KEY_a || ch == LEFT) { x--; }
	else if (ch == KEY_D || ch == KEY_d || ch == RIGHT) { x++; }
	else if (ch == KEY_W || ch == KEY_w || ch == UP) { y--; }
	else if (ch == KEY_S || ch == KEY_s || ch == DOWN) { y++; }
	else { return; }


	clip(maxx, maxy);
	eat(map);
}