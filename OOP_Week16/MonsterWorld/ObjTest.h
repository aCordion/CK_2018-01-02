#pragma once
#include <iostream>
#include <string>

using namespace std;

class ObjTest {
	string str;

public :
	ObjTest(string s="더미문자열") : str(s) {
		cout << "ObjTest 생성자 문자열 = " << str << endl;
	}
	~ObjTest() { cout << "ObjTest 소멸자  str = " << str << endl; }

};
