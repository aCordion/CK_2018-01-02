#pragma once
#include <iostream>
#include <string>
#include "Point.h"
#define MAXLINES 100
using namespace std;

class Canvas {
	string line[MAXLINES];	// ȭ�� ����� ���� ���ڿ�
	Point q;
	int xMax, yMax;		// ���� ũ��
public:
	Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
		q(nx, ny);
//		cout << "Canvas nx = " << nx << ", ny = " << ny << endl;
		for (int y = 0; y < yMax; y++)
			line[y] = string(xMax * 2, ' ');
	}
	void draw(int x, int y, string val);
	void draw(Point p, string val);  
	void clear(string val = ". "); 	// ����Ʈ �Ű�����: ���� 2��
	void print(char *title = "<My Canvas>");  
};