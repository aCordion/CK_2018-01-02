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

	ScreenInit();	// 화면 초기화

	while (true) {
		isContinue = true;
		game.rstMap(MAPSIZEX, MAPSIZEY, MINES);

		// game logic
		while (isContinue) {
			// draw call
			ScreenClear();	// 화면 지우기
			game.draw();

			if (game.getCheckStatus() == 0) {
				cursor.draw();
			}
			//		if (game.getCheckStatus() != 0) {
			else {
				game.allTileOpen();
				switch (game.getCheckStatus()) {
				case 1:
					ScreenPrint(0, MAPSIZEY + 5, "< 성공 >\n지뢰를 제외한 모든 타일을 열었습니다!\n");
					break;
				case 2:
					ScreenPrint(0, MAPSIZEY + 5, "< 실패 >\n지뢰가 폭발하였습니다.\n");
					break;
				}
			}
			/*
			int TmpClose, TmpOpen, TmpMines;
			TmpClose = game.getLeftTiles();
			TmpOpen = game.getOpenTiles();
			TmpMines = MINES;
			*/
			ScreenPrint(0, MAPSIZEY + 1, "방향키로 커서 이동, 'Space'키로 타일 확인");
			ScreenPrint(0, MAPSIZEY + 2, "'R'키를 눌러 다시 시작 합니다.\n'ESC'키를 눌러 종료합니다.");
			ScreenFlipping();	// 화면에 보여주기

			// 키보드 입력 처리
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
					if (nLeft == nOpen) {		//지뢰를 피해 타일을 모두 열 경우 상태값(checkStatus)에 성공(1 == win))을 대입
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
	/*		cout << "게임이 끝났습니다." << endl <<
				"다시 하시겠습니까?" << endl <<
				"[1] 다시 한다" << endl <<
				"[2] 종료 한다" << endl;
				*/
				/*
				printf("게임이 끝났습니다.\n다시 하시겠습니까?\n[1] 다시 한다\n[2] 종료 한다\n");
				switch (game.getNums(2)) {
				case 1: break;
				case 2: isContinue = false; break;
				}*/

	ScreenRelease();	//화면 해제
}