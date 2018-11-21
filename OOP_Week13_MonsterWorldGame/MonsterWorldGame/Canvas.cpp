#include "Canvas.h"
 
void Canvas::draw(int x, int y, string val) {
	if (x >= 0 && y >= 0 && x<xMax && y<yMax)
		line[y].replace(x * 2, 2, val);
}
void Canvas::clear(string val) {		// 디폴트 매개변수: 공백 2개
	for (int y = 0; y < yMax; y++)
		for (int x = 0; x < xMax; x++)
			draw(x, y, val);
}
void Canvas::print(char *title) {
	system("cls");
	cout << title << endl;
	for (int y = 0; y < yMax; y++)
		cout << line[y] << endl;
	cout << endl;
}