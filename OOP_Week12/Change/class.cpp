#include <iostream>

using namespace std;

class Calc {
protected:
	int a;
	int b;

public:
	Calc();
	Calc(int new_A, int new_B);
	virtual void print();
};
Calc::Calc() {
	cout << "Calc 클래스 기본 생성자......\n";
	a = 0; b = 0;
}
Calc::Calc(int new_A, int new_B) {
	cout << "Calc 클래스 파라미터 생성자......\n";
	a = new_A; b = new_B;
}
void Calc::print() {
	cout << "---------- Calc::Print ----------\n";
	cout << a << "\t" << b << endl;
}

class Add : public Calc{
protected:
	int c;

public:
	Add();
	Add(int new_A, int new_B);
	void sum();
	void print();
};
Add::Add() {
	cout << "Add 클래스 기본 생성자......\n";
}
Add::Add(int new_A, int new_B) : Calc(new_A, new_B) {
	cout << "Add 클래스 파라미터 생성자......\n";
	a = new_A; b = new_B;
}
void Add::sum(){
	c = a + b;
}
void Add::print() {
	cout << "---------- Add::Print ----------\n";
	cout << a << " + " << b << " = " << c << endl;
}


void main() {

	Add AddObject(3, 5);
	Add *AddPtr;
	AddPtr = &AddObject;
	AddPtr->sum();
	AddPtr->print();

	Calc *CalcPtr;
	CalcPtr = &AddObject;	// 업 캐스팅
	CalcPtr->print();	//해결할 과제	(Calc::print를 가상함수화);
	//CalcPtr->sum();	//

	Calc Object(10, 20);
	Add *AddPtr2;
	AddPtr2 = (Add*)&Object;	// 다운 캐스팅
	AddPtr2->print();
	//AddPtr2->sum();	//

	Calc *CalcPtr2;
	CalcPtr2 = new Add(7, 9);	//업 캐스팅
	
	Add *AddPtr3;
	AddPtr3 = (Add*)CalcPtr2;	//다운 캐스팅
	AddPtr3->print();
	AddPtr3->sum();
	AddPtr3->print();

}