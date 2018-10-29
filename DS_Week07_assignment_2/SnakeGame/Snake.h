#pragma once

#define MAX			1250
#define MIN			6

#define KEY_LEFT	75
#define KEY_UP		72
#define KEY_RIGHT	77
#define KEY_DOWN	80


struct snakeParts
{
	int x, y;
};

class CSnake
{
	snakeParts s_length[MAX];
//	snakeParts Temp[1];
	int oldDirection, curDirection;
	int count;
	int nCount;
	int maxSize;

public:
	CSnake();
	CSnake(int x = 2, int y = 2);
	~CSnake();

	void init();

	int getX(int pos) { return s_length[pos].x; }
	int getY(int pos) { return s_length[pos].y; }
//	int getPartType(int pos) { return s_length[pos].partType; }
//	int getCurDirection(int pos) { return s_length[pos].curDirection; }
//	snakeParts* getData() { return s_length; }

	int getLengthX() { return s_length[count].x; }
	int getLengthY() { return s_length[count].y; }

	int getCount() { return count; }

//	void setX(int pos, int value) { s_length[pos].x = value; }
//	void setY(int pos, int value) { s_length[pos].y = value; }
//	void setPartType(int pos, int value) { s_length[pos].partType = value; }
	void setCurDirection(int value) { curDirection = value; }
	void overideCount() { count = nCount; }

	void move();
	bool gameOver() { return true; }
	void eat();
	bool isCrash();

};

