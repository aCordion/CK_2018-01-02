#include "Canvas.h"
 
void Canvas::draw(int x, int y, string val) {
	if (x >= 0 && y >= 0 && x < xMax && y < yMax)
		line[y].replace(x * 2, 2, val);
}
void Canvas::draw(Point p, string val) {
	if (p[0] >= 0 && p[1] >= 0 && p[0] < xMax && p[1] < yMax)
		line[p[1]].replace(p[0] * 2, 2, val);
}
void Canvas::clear(string val) {		// 디폴트 매개변수: 공백 2개
	for (int y = 0; y < yMax; y++) {
		q[1] = y;
		for (int x = 0; x < xMax; x++) {
			q[0] = x;
			draw(q, val);
		}
	}
}
void Canvas::print(char *title) {
	system("cls");
	cout << title << endl;
	for (int y = 0; y < yMax; y++)
		cout << line[y] << endl;
	cout << endl;
}