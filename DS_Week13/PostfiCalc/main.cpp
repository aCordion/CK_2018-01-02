#include <iostream>
//#include <stdio.h>
//#include <string>
#include "ArrayStack.h"
#include "MyCalc.h"

using namespace std;


void main() {

	CMyCalc simpleCalc(100);

	char testForm[100];	//������ ������ �迭

	cout << "postFix �Է� : ";
	cin.getline(testForm, 100);
	simpleCalc.setPostFix(testForm);	//������ ����� �Է�
	simpleCalc.calc();
	simpleCalc.draw();
}
