#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

class CTimeOpClass
{
	int hour, min, sec, total;

public:
	CTimeOpClass(int h, int m, int s) : hour(h), min(m), sec(s) {
		total = convert(h, m, s);
	}
	CTimeOpClass(int d = 0) { total = d; convert(d); }
	~CTimeOpClass() {}

	void convert(int total) {
		this->total = total;
		hour = total / (60 * 60);
		total %= (60 * 60);
		min = total / 60;
		sec = total % 60;
	}

	int convert(int h, int m, int s) {
		total = (h * 360) + (m * 60) + s;
		return total;
	}


	int totalsec() {
		return hour * (60 * 60) + min * 60 + sec;
	}

	friend ostream& operator<< (ostream& os, const CTimeOpClass& t) {
		os << t.hour << " ½Ã, " << t.min << " ºÐ, " << t.sec << " ÃÊ.";
		return os;
	}
	friend istream& operator >> (istream& is, CTimeOpClass& t) {
		int temp;
		is >> temp;
		t.convert(temp);
		return is;
	}

	CTimeOpClass operator+ (CTimeOpClass& a) {
		CTimeOpClass sum(total + a.total);
		return sum;
	}

	CTimeOpClass operator- (CTimeOpClass& a) {
		CTimeOpClass temp(total - a.total);
		return temp;
	}

	CTimeOpClass operator++() {
		total += 3600;
		convert(total);
		return total;
	}

	CTimeOpClass operator--() {
		total -= 3600;
		convert(total);
		return total;
	}

	CTimeOpClass operator++(int) {
		++total;
		convert(total);
		return total;
	}

	CTimeOpClass operator--(int) {
		--total;
		convert(total);
		return total;
	}

	int& operator[] (int id) {
		switch (id) {
		case 0: return hour;
		case 1: return min;
		case 2: return sec;
		case 3: return total;
		}
	}

	operator int() {
		return total;
	}

	operator double() {
		return total / (60 * 60);
	}

	CTimeOpClass operator* (int a) {
		CTimeOpClass temp(total * a);
		return temp;
	}

	friend CTimeOpClass operator* (int a, CTimeOpClass& b) {
		CTimeOpClass temp(b.total*a);
		return temp;
	}
};