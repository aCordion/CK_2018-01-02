#pragma once
#include <iostream>
#include <string>

using namespace std;

class ObjTest {
	string str;

public :
	ObjTest(string s="���̹��ڿ�") : str(s) {
		cout << "ObjTest ������ ���ڿ� = " << str << endl;
	}
	~ObjTest() { cout << "ObjTest �Ҹ���  str = " << str << endl; }

};
