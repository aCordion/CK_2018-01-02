#include "Shape.h"

Point readPoint() {
	Point p;
	cout << "좌표를 입력해주세요 (x, y) = ";
	cin >> p.x >> p.y;
	return p;	//Point p 는 로컬변수이기 때문에 반환할 때 컴파일러가 임의로 Point p 를 복제하여 반환. 그래서 소멸자가 실행됨
}

void printPoint(Point p, char* str = "Point") {
	cout << str << " = (" << p.x << " , " << p.y << ") \n";
}