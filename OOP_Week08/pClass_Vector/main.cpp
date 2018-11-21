#include "Vector.h"

void main() {
	CVector u(3), v(5), w;

	u.setRand();
	v.setRand();

	//대입에 의한 복사 생성자의 얕은 복사에 의한 에러
	{
//		w = u;
//		w.clone(u);	//깊은 복사
		w = u;	//오퍼레이터 오버라이딩 void operator = (CVector & a) { clone(a); }

		u.print();
		v.print();
		w.print();
	}

	{
		//w.add(u, v);
		w.add(&u, &v);
		w.print(" U + V = ");
	}

	/*
	u.print(" U ");
	v.print(" V ");
	w.print(" W ");
	*/
}