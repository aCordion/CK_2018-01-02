#pragma once
#include <iostream>

using namespace std;

class Calc
{
protected:
	int a, b, c;

public:
	Calc();
	Calc(int new_A, int new_B);
	~Calc();
	void Init(int new_A, int new_B);
	void Prn();
};

Calc::Calc(){
	cout << "Calc ��� Ŭ���� �⺻ ������......\n";
}

Calc::Calc(int new_A, int new_B) {
	cout << "Calc ��� Ŭ���� ��� �ʱ�ȭ ������......\n";
	a = new_A;
	b = new_B;
	c = 0;
}
Calc::~Calc() {
	cout << "Calc ��� Ŭ���� �⺻ �Ҹ���......\n";
}

void Calc::Init(int new_A, int new_B) {
	a = new_A;
	b = new_B;
	c = 0;
}

void Calc::Prn() {
	cout << a << "\t" << b << "\t" << c << endl;
}

class Add : public Calc {

public:
	Add();
	Add(int new_A, int new_B);
	~Add();
	void sum();
};

Add::Add() {
	cout << "Add �Ļ� Ŭ���� �⺻ ������......\n";
}

Add::Add(int new_A, int new_B) : Calc(new_A, new_B) {
	cout << "Add �Ļ� Ŭ���� ��� �ʱ�ȭ ������......\n";
	a = new_A;
	b = new_B;
	c = 0;
}
Add::~Add() {
	cout << "Add �Ļ� Ŭ���� �⺻ �Ҹ���......\n";
}

void Add::sum() {
	c = a + b;
}

class Mul : public Calc {
public:
	void Gob();
	Mul();
	Mul(int new_A, int new_B);
	~Mul();
};

Mul::Mul() {
	cout << "Mul �Ļ� Ŭ���� �⺻ ������......\n";
}

Mul::Mul(int new_A, int new_B) : Calc(new_A, new_B) {
	cout << "Mul �Ļ� Ŭ���� ��� �ʱ�ȭ ������......\n";
	a = new_A;
	b = new_B;
	c = 0;
}
Mul::~Mul() {
	cout << "Mul �Ļ� Ŭ���� �⺻ �Ҹ���......\n";
}

void Mul::Gob() {
	c = a * b;
}

void main() {
	Add x;
	x.Init(3,5);
	x.sum();
	x.Prn();

	Mul y;
	y.Init(2, 7);
	y.Gob();
	y.Prn();
}