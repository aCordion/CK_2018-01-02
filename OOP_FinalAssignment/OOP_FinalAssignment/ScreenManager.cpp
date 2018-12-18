#include "ScreenManager.h"




CScreenManager::CScreenManager(int nx, int ny) : xMax(nx), yMax(ny)
{
	bBufFlip = false;
	for (int y = 0; y < yMax; y++) {
		line[y] = string(xMax * 2, ' ');
		line2[y] = string(xMax * 2, ' ');
	}
}


CScreenManager::~CScreenManager()
{
}

void CScreenManager::draw(int x, int y, string val)
{
	if (x >= 0 && y >= 0 && x < xMax && y < yMax) {
		if (!bBufFlip) {
			line[y].replace(x * 2, 2, val);
		}
		else {
			line2[y].replace(x * 2, 2, val);
		}
	}
}

void CScreenManager::clear(string val)
{
	for (int y = 0; y < yMax; y++) {
		for (int x = 0; x < xMax; x++) {
			draw(x, y, val);
		}
	}
}


void CScreenManager::print(char * title)
{
	system("cls");

	cout << title << endl;
	for (int y = 0; y < yMax; y++) {
		if (bBufFlip) {
			cout << line[y] << endl;
		}
		else {
			cout << line2[y] << endl;
		}
	}
	bBufFlip = !bBufFlip;
	cout << endl;
}
