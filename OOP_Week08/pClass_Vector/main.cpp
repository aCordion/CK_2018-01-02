#include "Vector.h"

void main() {
	CVector u(3), v(5), w;

	u.setRand();
	v.setRand();

	//���Կ� ���� ���� �������� ���� ���翡 ���� ����
	{
//		w = u;
//		w.clone(u);	//���� ����
		w = u;	//���۷����� �������̵� void operator = (CVector & a) { clone(a); }

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