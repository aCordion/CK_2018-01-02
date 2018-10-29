#pragma once
#include "Snake.h"

#include <iostream>
#include <fstream>

using namespace std;

CSnake::CSnake()
{
	int x = 2, y = 2;

	for (int i = 0; i < MAX; i++) {
		s_length[i] = { 0, 0 };
	}
	for (int i = 0; i < MIN; i++) {
		s_length[i] = { x, y+1 };
		count = (i);
	}
	s_length[0] = { 2, 2 };

	curDirection = KEY_RIGHT;
	oldDirection = curDirection;
	nCount = count;
	maxSize = MAX;
}


CSnake::CSnake(int x, int y)
{

	for (int i = 0; i < MAX; i++) {
		s_length[i] = { 0, 0 };
	}

	for (int i = 0; i < MIN; i++) {
		s_length[i] = { x, y+1 };
		count = (i);
	}
	s_length[0] = { 2, 2 };

	curDirection = KEY_RIGHT;
	oldDirection = curDirection;
	nCount = count;
	maxSize = MAX;

}

CSnake::~CSnake()
{
}

void CSnake::init()
{
	int x = 2, y = 2;

	for (int i = 0; i < MAX; i++) {
		s_length[i] = { 0, 0 };
	}
	for (int i = 0; i < MIN; i++) {
		s_length[i] = { x, y + 1 };
		count = (i);
	}
	s_length[0] = { 2, 2 };

	curDirection = KEY_RIGHT;
	oldDirection = curDirection;
	nCount = count;
	maxSize = MAX;
}

void CSnake::move()
{

//	snakeParts tempLength1 = s_length[0];
//	snakeParts tempLength2;

//	int tempX1 = 0, tempY1 = 0;

	int tempX1 = s_length[0].x;
	int tempY1 = s_length[0].y;
	int tempX2 = 2;
	int tempY2 = 2;
	int dirCheck;

	if (oldDirection == KEY_DOWN && curDirection == KEY_UP) { curDirection = oldDirection; }
	if (oldDirection == KEY_UP && curDirection == KEY_DOWN) { curDirection = oldDirection; }
	if (oldDirection == KEY_RIGHT && curDirection == KEY_LEFT) { curDirection = oldDirection; }
	if (oldDirection == KEY_LEFT && curDirection == KEY_RIGHT) { curDirection = oldDirection; }

	switch (curDirection) {
	case KEY_UP:
		s_length[0].y--;
		if (s_length[0].y <= 0) {
			gameOver();
		}
		break;
	case KEY_DOWN:
		s_length[0].y++;
		if (s_length[0].y >= 24) {
			gameOver();
		}
		break;
	case KEY_LEFT:
		s_length[0].x--;
		if (s_length[0].x <= 0) {
			gameOver();
		}
		break;
	case KEY_RIGHT:
		s_length[0].x++;
		if (s_length[0].y >= 52) {
			gameOver();
		}
		break;
	}
	oldDirection = curDirection;
/*
	int tempX1 = s_length[pos].x, tempY1 = s_length[pos].y;
	int tempX2 = 0, tempY2 = 0;
	*/

	int i = 1;
	bool isContinue = true;
	while (isContinue)
	{
		if (i > count) { isContinue = false; }
		tempX2 = s_length[i].x;
		tempY2 = s_length[i].y;
		s_length[i].x = tempX1;
		s_length[i].y = tempY1;
		i++;

		if (i > count) { isContinue = false; }
		tempX1 = s_length[i].x;
		tempY1 = s_length[i].y;
		s_length[i].x = tempX2;
		s_length[i].y = tempY2;
		i++;

	}


//	bool flipFlop = true;
	/*
	for(int i = 0; i < count; i++){

		if (flipFlop) {
			tempX2 = s_length[i].x;
			tempY2 = s_length[i].y;
			s_length[i].x = tempX1;
			s_length[i].y = tempY1;
			flipFlop = false;
		}
		else if (!flipFlop) {
			tempX1 = s_length[i].x;
			tempY1 = s_length[i].y;
			s_length[i].x = tempX2;
			s_length[i].y = tempY2;
			flipFlop = true;
		}
		*/
	/*
	for (int i = 1; i < count; i++) {
		if (flipFlop) {
			tempLength2 = s_length[i];
			s_length[i] = tempLength1;
			flipFlop = false;
		}
		else {
			tempLength1 = s_length[i];
			s_length[i] = tempLength2;
			flipFlop = true;
		}

	}
	*/
	isCrash();
}



void CSnake::eat()
{
	int temp = count;
	temp += 2;
	nCount = temp;
}

bool CSnake::isCrash()
{
	for (int i = 2; i <= (count-1); i++) {
		if ((s_length[0].x == s_length[i].x) && (s_length[0].y == s_length[i].y)) {
			return true;
		}
	}
	return false;
}

