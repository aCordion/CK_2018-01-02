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
	cout << "Calc 기반 클래스 기본 생성자......\n";
}

Calc::Calc(int new_A, int new_B) {
	cout << "Calc 기반 클래스 멤버 초기화 생성자......\n";
	a = new_A;
	b = new_B;
	c = 0;
}
Calc::~Calc() {
	cout << "Calc 기반 클래스 기본 소멸자......\n";
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
	cout << "Add 파생 클래스 기본 생성자......\n";
}

Add::Add(int new_A, int new_B) : Calc(new_A, new_B) {
	cout << "Add 파생 클래스 멤버 초기화 생성자......\n";
	a = new_A;
	b = new_B;
	c = 0;
}
Add::~Add() {
	cout << "Add 파생 클래스 기본 소멸자......\n";
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
	cout << "Mul 파생 클래스 기본 생성자......\n";
}

Mul::Mul(int new_A, int new_B) : Calc(new_A, new_B) {
	cout << "Mul 파생 클래스 멤버 초기화 생성자......\n";
	a = new_A;
	b = new_B;
	c = 0;
}
Mul::~Mul() {
	cout << "Mul 파생 클래스 기본 소멸자......\n";
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