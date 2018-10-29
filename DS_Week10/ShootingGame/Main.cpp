#include "GameMap.h"
#include "util.h"
#include "Player.h"
#include "pBullet.h"

#include <Windows.h>
#include <time.h>
#include <conio.h>

#define MAPSIZEX 15
#define MAPSIZEY 20

void main() {
	srand((unsigned int)time(NULL));
	CGameMap game(MAPSIZEX, MAPSIZEY);
	CPlayer player(MAPSIZEX/2, MAPSIZEY-2, MAPSIZEX, MAPSIZEY);
	CpBullet pBullet(MAPSIZEX, MAPSIZEY);

	clock_t oldTime, curTime;
	oldTime = clock();

	bool isContinue;

	ScreenInit();	// ȭ�� �ʱ�ȭ

	while (true) {
		isContinue = true;
		game.setMap(MAPSIZEX, MAPSIZEY);

		// game logic
		while (isContinue) {
			// draw call
			ScreenClear();	// ȭ�� �����
			game.draw();
			player.draw();
			pBullet.bulletGoUp();
//			pBullet.bulletDestroy();
			pBullet.draw();
			ScreenPrint(0, MAPSIZEY + 1, "��,�� (��, ��)����Ű�� Ŀ�� �̵�, 'Space'Ű�� źȯ �߻�");
			ScreenPrint(0, MAPSIZEY + 2, "'R'Ű�� ���� �ٽ� ���� �մϴ�.\n'ESC'Ű�� ���� �����մϴ�.");
			ScreenFlipping();	// ȭ�鿡 �����ֱ�

			// Ű���� �Է� ó��
			int nKey;
			if (_kbhit()) {	//if keyboard is pressed
				nKey = _getch();
				switch (nKey) {
				case LEFT:
				case '4':
					player.goLeft();
					break;
				case RIGHT:
				case '6':
					player.goRight();
					break;
				case SPACE:
				case '0':
				{
					int x = player.getX();
					int y = player.getY();

					pBullet.append(x, y);
//					pBullet.insert(0, x, y-1);

				}
				break;
				case KEY_R:
				case KEY_r:
					isContinue = false;
					break;
				case ESC:
					return;
				}

				while (1) {
					curTime = clock();
					if (curTime - oldTime > 33) {	//33
						oldTime = curTime;
						break;
					}
				}
			}
			if (isContinue == false) {
				break;
			}
		}
	}

	ScreenRelease();	//ȭ�� ����
}