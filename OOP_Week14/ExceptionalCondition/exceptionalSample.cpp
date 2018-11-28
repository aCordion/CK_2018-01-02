#include <iostream>

using namespace std;

void efunc(int a) throw(char*, int) {
	if (a == 0) {
		throw "변수값이 0 입니다";
	}
	else {
		throw a;
	}
}

void main() {

	int a, b, c, d;

	cout << "나눗셈을 하기 위한 데이터를 입력하시오." << endl;
	cout << "나누는 수(피제수)를 입력하시오 = ";
	cin >> a;
	
	cout << "나누는 수(피수)를 입력하시오 = ";
	cin >> b;
	try {
		if (b == 0) { throw b; }
		c = a / b;
		cout << "몫 => " << c << endl;
		d = a % b;
		cout << "나머지 => " << d << endl;
	}
	catch(int ex){
		cout << ex << "로 나누려는 시도가 발생했으므로 예외로 처리합니다.\n";
	}
	cout << "예외가 발생하더라도 정상적으로 종료합니다...\n";

	try {
		efunc(0);
	}
	catch (char *str) {
		cout << str << endl;
	}
	catch (int ex) {
		cout << "숫자 " << ex << " 로 인한 예외발생.......\n";
	}

	/*if (b == 0) {
		cout << "예외 상황이 발생했습니다......\n";
	}
	else {
		c = a / b;
		cout << "몫 => " << c << endl;
		d = a % b;
		cout << "나머지 => " << d << endl;
	}*/


}