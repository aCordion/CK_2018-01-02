#pragma once
#include "Snake.h"
#include "Matrix.h"
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define KEY_ESCAPE	27
#define KEY_ENTER	13

#define TIME_WAIT 150

extern enum eTileType { BLANK = 0, WALL = 1, FOOD = 2, SNAKE = 3 };

void main() {
	system("mode con:cols=120 lines=30");
	system("title SnakeGame");

	srand((unsigned int)time(NULL));


	CMatrix map;
	CSnake snake(2, 2);
	clock_t oldTime, curTime;
	while (true) {
		bool isContinue = true;
		bool isGameOver = false;
		bool isFoodEat = true;
		bool isTailCrash = false;
		bool isWallCrash = false;

		oldTime = clock();
		int x, y, count;

		while (isContinue) {

			count = snake.getCount();
			snake.move();
			for (int i = 0; i < count; i++) {
				x = snake.getX(i);
				y = snake.getY(i);
				/*			if (( i == 0 ) && ( map.elem(x, y) == FOOD )) {
								snake.eat();
								map.bSetFood(false);
							}
							*/
				if (i == 0 && map.elem(x, y) == FOOD) {
					snake.eat();
					isFoodEat = true;
					map.bSetFood(!isFoodEat);
				}
				map.setMat(x, y, SNAKE);
			}
			map.setMat(x, y, BLANK);
			if (!map.bGetFood()) {
				//			snakeParts *Temp = NULL;
				//			Temp = snake.getData();
				//			map.setFood(*Temp);
				map.setFood();
			}
			system("cls");
			map.print();
			cout << "뱀 길이 : " << snake.getCount() - 1 << endl;
			if (snake.isCrash() || map.wallCrash()) {
				cout << "게임 오버!!" << endl;
				isGameOver = true;
			}
			while (true) {
				curTime = clock();
				if (_kbhit()) {
					int dir = _getch();
					if (dir == KEY_UP || dir == KEY_DOWN || dir == KEY_LEFT || dir == KEY_RIGHT) {
						snake.setCurDirection(dir);
					}
				}
				if (curTime - oldTime > TIME_WAIT) {
					oldTime = curTime;
					break;
				}
			}
			if (isFoodEat) {
				isFoodEat = false;
				snake.overideCount();
			}
			if (isGameOver) {
				Sleep(1000);
				cout << "다시 하시겠습니까?" << endl <<
					"Yes (Enter Key), No (ESC Key)" << endl;
				while (isGameOver) {
					if (_kbhit()) {
						int Choice = _getch();
						switch (Choice)
						{
						case KEY_ENTER:
							map.init();
							map.bSetFood(false);
							map.setFood();
							snake.init();
							isContinue = false;
							isGameOver = false;
							break;
						case KEY_ESCAPE:
							exit(0);
							break;
						}
					}
				}
			}
		}
	}
}