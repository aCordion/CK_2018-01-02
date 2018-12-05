#include "Human.h"


void Human::move(int ** map, int maxx, int maxy)
{
	if (_kbhit()) {
		char ch = getDirKey();
		if (ch == LEFT) { p[0]--; }
		else if (ch == RIGHT) { p[0]++; }
		else if (ch == UP) { p[1]--; }
		else if (ch == DOWN) { p[1]++; }
		else { return; }

		clip(maxx, maxy);
		eat(map);
	}
}

void Tuman::moveHuman(int ** map, int maxx, int maxy, char ch)
{
	if (ch == KEY_A || ch == KEY_a || ch == LEFT) { p[0]--; }
	else if (ch == KEY_D || ch == KEY_d || ch == RIGHT) { p[0]++; }
	else if (ch == KEY_W || ch == KEY_w || ch == UP) { p[1]--; }
	else if (ch == KEY_S || ch == KEY_s || ch == DOWN) { p[1]++; }
	else { return; }


	clip(maxx, maxy);
	eat(map);
}