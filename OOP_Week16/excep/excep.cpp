#include <iostream>
#include <cassert>

using namespace std;

void onExit() { cout << "......... 프로그램 종료 함수 .........\n"; }
void divide(int a, int b) {
	int c, d;

	cout << "********* Divide 함수 *********\n";

	if (b == 0) throw b; //예외

	c = a / b;
	cout << "몫 => " << c << endl;
	d = a % b;
	cout << "나머지 => " << d << endl;
}
void efunc(int a) throw(char *, int) {
	if (a == 0) throw "변수의 값이 0임";
	else {
		throw a;
	}
}

class UserError {
public:
	void func();
};

void UserError::func() {
	cout << "사용자 정의 예외......\n";
}
void main() {

	atexit(onExit);

	//int a, b, c, d;
	//cout << " 나눗셈을 하기 위한 데이터를 입력하시오......\n";
	//cout << "나누는 수(피제수)를 입력하시오 = ";
	//cin >> a;
	//cout << "나누는 수(제수)를 입력하시오 = ";
	//cin >> b;

	///*if (b == 0) {
	//	cout << " 예외 상황이 발생했습니다......\n";
	//	exit(0);
	//}

	//c = a / b;

	//cout << "몫 => " << c << endl;

	//d = a % d;

	//cout << "나머지 => " << d << endl;*/
	//try {
	//	if (b == 0) throw b;
	//	c = a / b;
	//	cout << "몫 => " << c << endl;
	//	d = a % b;
	//	cout << "나머지 => " << d << endl;
	//}
	//catch (int ex) {
	//	cout << ex << " 로 나누려는 시도가 확인되어 예외로 처리합니다...\n";
	//}
	//cout << "예외가 발생하더라도 항상 실행...\n";

	//try {
	//	divide(10, 2);
	//	divide(10, 0);
	//	divide(10, 4);
	//}
	//catch (int ex) {
	//	cout << ex << " 로 나누려는 시도가 확인되어 예외로 처리합니다...\n";
	//}
	/*int a;
	cout << "수를 입력하시오 = ";
	cin >> a;

	try {
		efunc(a);
	}
	catch (char *str) {
		cout << str << endl;
	}
	catch (int ex) {
		cout << ex << " 숫자로 인한 예외발생......\n";
	}
*/
	try {

		throw UserError();

	}
	catch (UserError &ex) {
		cout << "사용자 정의 예외 발생 처리......\n";
		ex.func();
	}
}