#pragma once
#include <iostream>
#include <string>
#include "Point.h"
#include "MyVector.h"
#define MAXLINES 100
using namespace std;

class Canvas {
	//string line[MAXLINES];	// 화면 출력을 위한 문자열
	Vector<string> line;
	Point q;
	int xMax, yMax;		// 맵의 크기
public:
	Canvas(int nx = 10, int ny = 10) : line(ny), xMax(nx), yMax(ny) {
		q(nx, ny);
//		cout << "Canvas nx = " << nx << ", ny = " << ny << endl;
		for (int y = 0; y < yMax; y++)
			line[y] = string(xMax * 2, ' ');
	}
	void draw(int x, int y, string val);
	void draw(Point p, string val);  
	void clear(string val = ". "); 	// 디폴트 매개변수: 공백 2개
	void print(char *title = "<My Canvas>");  
};