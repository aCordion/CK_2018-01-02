#include "GameMap.h"
#include "util.h"
#include "MyCursor.h"
#include <Windows.h>
#include <time.h>
#include <conio.h>

#define MAPSIZEX 10
#define MAPSIZEY 10
#define MINES	 5

void main() {
	srand((unsigned int)time(NULL));
	CGameMap game(MAPSIZEX, MAPSIZEY, MINES);
	CMyCursor cursor(0, 0, MAPSIZEX, MAPSIZEY);

	clock_t oldTime, curTime;
	oldTime = clock();

	bool isContinue;
	int nLeft, nOpen;

	ScreenInit();	// ȭ�� �ʱ�ȭ

	while (true) {
		isContinue = true;
		game.rstMap(MAPSIZEX, MAPSIZEY, MINES);

		// game logic
		while (isContinue) {
			// draw call
			ScreenClear();	// ȭ�� �����
			game.draw();

			if (game.getCheckStatus() == 0) {
				cursor.draw();
			}
			//		if (game.getCheckStatus() != 0) {
			else {
				game.allTileOpen();
				switch (game.getCheckStatus()) {
				case 1:
					ScreenPrint(0, MAPSIZEY + 5, "< ���� >\n���ڸ� ������ ��� Ÿ���� �������ϴ�!\n");
					break;
				case 2:
					ScreenPrint(0, MAPSIZEY + 5, "< ���� >\n���ڰ� �����Ͽ����ϴ�.\n");
					break;
				}
			}
			/*
			int TmpClose, TmpOpen, TmpMines;
			TmpClose = game.getLeftTiles();
			TmpOpen = game.getOpenTiles();
			TmpMines = MINES;
			*/
			ScreenPrint(0, MAPSIZEY + 1, "����Ű�� Ŀ�� �̵�, 'Space'Ű�� Ÿ�� Ȯ��");
			ScreenPrint(0, MAPSIZEY + 2, "'R'Ű�� ���� �ٽ� ���� �մϴ�.\n'ESC'Ű�� ���� �����մϴ�.");
			ScreenFlipping();	// ȭ�鿡 �����ֱ�

			// Ű���� �Է� ó��
			int nKey;
			if (_kbhit()) {	//if keyboard is pressed
				nKey = _getch();
				switch (nKey) {
				case UP:
				case '8':
					cursor.goUp();
					break;
				case DOWN:
				case '5':
					cursor.goDown();
					break;
				case LEFT:
				case '4':
					cursor.goLeft();
					break;
				case RIGHT:
				case '6':
					cursor.goRight();
					break;
				case SPACE:
				case '0':
				{
					int x = cursor.getX();
					int y = cursor.getY();
					//				game.setTile(x, y, true);
					game.rcTileOpenner(x, y);

					/*
					nLeft = game.getLeftTiles();
					nOpen = game.getOpenTiles();
					if (nLeft == nOpen) {		//���ڸ� ���� Ÿ���� ��� �� ��� ���°�(checkStatus)�� ����(1 == win))�� ����
						game.setCheckStatus(1);
					}
					*/
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
					if (curTime - oldTime > 33) {
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
	//		gotoxy(0, MAPSIZEY + 3);
	/*		cout << "������ �������ϴ�." << endl <<
				"�ٽ� �Ͻðڽ��ϱ�?" << endl <<
				"[1] �ٽ� �Ѵ�" << endl <<
				"[2] ���� �Ѵ�" << endl;
				*/
				/*
				printf("������ �������ϴ�.\n�ٽ� �Ͻðڽ��ϱ�?\n[1] �ٽ� �Ѵ�\n[2] ���� �Ѵ�\n");
				switch (game.getNums(2)) {
				case 1: break;
				case 2: isContinue = false; break;
				}*/

	ScreenRelease();	//ȭ�� ����
}