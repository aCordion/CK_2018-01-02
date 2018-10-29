#include "MyCursor.h"
#include "util.h"
#include "GameMap.h"
#include <time.h>
#include <conio.h>


void main() {
	CMyCursor myCursor(5, 10, 40, 25);
	CGameMap gameMap(40, 25);

	time_t oldTime, curTime;
	oldTime = clock();
	bool isContinue = true;
	int actKey;

	ScreenInit();	//화면 초기화, 한번만 호출하면 됨
	// Game Logic
	while (isContinue)
	{
		bool actKeyPushed = false;

		int nKey;
		if (_kbhit()) {
			nKey = _getch();
			switch (nKey) {
			case UP:
			case 'w':
				myCursor.goUp();
				break;
			case DOWN:
			case 's':
				myCursor.goDown();
				break;
			case LEFT:
			case 'a':
				myCursor.goLeft();
				break;
			case RIGHT:
			case 'd':
				myCursor.goRight();
				break;
//			case SPACE:
//				bSpace = true;
//				break;

			case KEY_Z:
			case KEY_z:
			case KEY_X:
			case KEY_x:
			case KEY_C:
			case KEY_c:
				actKeyPushed = true;
				actKey = nKey;
				break;
			}	// end of switch
		}	//end of if

		// draw call
		ScreenClear();
		gameMap.draw();
		myCursor.draw();
		if (actKeyPushed) {
			gameMap.actDraw(myCursor.getX(), myCursor.getY(), actKey);
			actKey = NULL;
		}
		int posMap = gameMap.getTileNum(myCursor.getX(), myCursor.getY());
		gameMap.curStatDraw(myCursor.getX(), myCursor.getY());
		ScreenFlipping();


		while (1) {
			curTime = clock();
			if (curTime - oldTime > 33) {
				oldTime = curTime;
				break;
			}
		}
	}	//end of while
	ScreenRelease();
}