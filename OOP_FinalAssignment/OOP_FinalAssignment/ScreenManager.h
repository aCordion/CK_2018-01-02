#pragma once
#include <iostream>
#include <string>
#include "Position.h"

#define ENTER	13
#define LEFT    75
#define RIGHT   77
#define UP		72
#define DOWN	80
#define SPACE	32
#define KEY_R	82
#define KEY_r	114
#define ESC		27

#define MAXLINES 100

using namespace std;

class CScreenManager
{
	string line[MAXLINES];
	string line2[MAXLINES];
	bool bBufFlip;
	int xMax, yMax;

public:
	CScreenManager(int nx = 60, int ny = 20);
	~CScreenManager();
	void draw(int x, int y, string val);
	void clear(string val = "  ");
	void print(char *title = "<My Game>");
};