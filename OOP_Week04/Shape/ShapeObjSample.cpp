#include "Shape.h"

Point readPoint() {
	Point p;
	cout << "��ǥ�� �Է����ּ��� (x, y) = ";
	cin >> p.x >> p.y;
	return p;	//Point p �� ���ú����̱� ������ ��ȯ�� �� �����Ϸ��� ���Ƿ� Point p �� �����Ͽ� ��ȯ. �׷��� �Ҹ��ڰ� �����
}

void printPoint(Point p, char* str = "Point") {
	cout << str << " = (" << p.x << " , " << p.y << ") \n";
}