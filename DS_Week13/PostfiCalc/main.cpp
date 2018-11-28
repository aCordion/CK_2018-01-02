#include <iostream>
//#include <stdio.h>
//#include <string>
#include "ArrayStack.h"
#include "MyCalc.h"

using namespace std;


void main() {

	CMyCalc simpleCalc(100);

	char testForm[100];	//수식을 저장할 배열

	cout << "postFix 입력 : ";
	cin.getline(testForm, 100);
	simpleCalc.setPostFix(testForm);	//수식을 계산기로 입력
	simpleCalc.calc();
	simpleCalc.draw();
}
