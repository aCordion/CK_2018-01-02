#include <iostream>
using namespace std;

class Test {
	int value;
public:
	Test(int v) {
		value = v;
	}
	void setValue(int v);
	int getValue();
};

void Test::setValue(int v) {
	value = v;
}
int Test::getValue() {
	return value;
}

template<typename DATATYPE>
class TestT {
	DATATYPE value;
public:
	TestT(DATATYPE v) {
		value = v;
	}
	void setValue(DATATYPE v);
	DATATYPE getValue();
};
template<typename DATATYPE>
void TestT<DATATYPE>::setValue(DATATYPE v) {
	value = v;
}
template<typename DATATYPE>
DATATYPE TestT<DATATYPE>::getValue() {
	return value;
}

template<typename TYPE, typename ARG_TYPE>
class Data {
	TYPE value;
public:
	Data(TYPE v);
	void copyData(ARG_TYPE v);
	TYPE getData();
};

template<typename TYPE, typename ARG_TYPE>
Data<TYPE, ARG_TYPE>::Data(TYPE v) {
	value = v;
}

template<typename TYPE, typename ARG_TYPE>
void Data<TYPE, ARG_TYPE>::copyData(ARG_TYPE v) {
	value = v;
}
template<typename TYPE, typename ARG_TYPE>
TYPE Data<TYPE, ARG_TYPE>::getData() {
	return value;
}

void main() {

	TestT<int> obj1(10);
	cout << "obj1 value = " << obj1.getValue() << endl;
	obj1.setValue(100);
	cout << "obj1 value = " << obj1.getValue() << endl;

	TestT<double> obj2(5.7);
	cout << "obj2 value = " << obj2.getValue() << endl;

	//class template 2°³ type ÁöÁ¤
	int a = 100;
	Data<int, int&>objdata(10);
	cout << "objdata data = " << objdata.getData() << endl;

	objdata.copyData(a);
	cout << "objdata data = " << objdata.getData() << endl;


	double b = 3.4;
	Data<double, double&> objdata2(10.5);
	cout << "objdata2 data = " << objdata2.getData() << endl;
	objdata2.copyData(b);
	cout << "objdata2 data = " << objdata2.getData() << endl;


}