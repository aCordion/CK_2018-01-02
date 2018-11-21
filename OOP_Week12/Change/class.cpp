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
	cout << "Calc Ŭ���� �⺻ ������......\n";
	a = 0; b = 0;
}
Calc::Calc(int new_A, int new_B) {
	cout << "Calc Ŭ���� �Ķ���� ������......\n";
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
	cout << "Add Ŭ���� �⺻ ������......\n";
}
Add::Add(int new_A, int new_B) : Calc(new_A, new_B) {
	cout << "Add Ŭ���� �Ķ���� ������......\n";
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
	CalcPtr = &AddObject;	// �� ĳ����
	CalcPtr->print();	//�ذ��� ����	(Calc::print�� �����Լ�ȭ);
	//CalcPtr->sum();	//

	Calc Object(10, 20);
	Add *AddPtr2;
	AddPtr2 = (Add*)&Object;	// �ٿ� ĳ����
	AddPtr2->print();
	//AddPtr2->sum();	//

	Calc *CalcPtr2;
	CalcPtr2 = new Add(7, 9);	//�� ĳ����
	
	Add *AddPtr3;
	AddPtr3 = (Add*)CalcPtr2;	//�ٿ� ĳ����
	AddPtr3->print();
	AddPtr3->sum();
	AddPtr3->print();

}