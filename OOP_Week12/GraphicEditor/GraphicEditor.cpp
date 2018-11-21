#include "Shape.h"

void main() {
	/*
	CCanvas myCanvas(25, 15);
	Line	l(2, 2, 8, 4);
	Rect	r(2, 9, 6, 3);
	HLine	h(1, 7, 23);
	VLine	v(12, 1, 13);
	Square	s(17, 1, 4);
	Circle	c(19, 11, 2);

	do {
		myCanvas.clear();
		l.draw(myCanvas, "●");
		r.draw(myCanvas, "▣");
		v.draw(myCanvas, "||");
		h.draw(myCanvas, "--");
		s.draw(myCanvas, "■");
		c.draw(myCanvas);

		myCanvas.print("나의 그림판");

		l.move(rand() % 3 - 1, rand() % 3 - 1);
		r.move(rand() % 3 - 1, rand() % 3 - 1);
		s.move(rand() % 3 - 1, rand() % 3 - 1);
		c.move(rand() % 3 - 1, rand() % 3 - 1);
	} while (getchar() != 'q');
	*/

	CCanvas myCanvas(25, 25);

	Shape* list[100];
	int nShape = 0;

	while (true) {
		myCanvas.print("< 내 마음대로 그릴 수 있는 나의 그래픽 편집기... >");
		char type;
		int v[4];
		printf("Input ===> ");
		cin >> type;
		if (type == 'l') {
			cin >> v[0] >> v[1] >> v[2] >> v[3];
			list[nShape++] = new Line(v[0], v[1], v[2], v[3]);
		}
		else if (type == 'v') {
			cin >> v[0] >> v[1] >> v[2];
			list[nShape++] = new VLine(v[0], v[1], v[2]);
		}
		else if (type == 'h') {
			cin >> v[0] >> v[1] >> v[2];
			list[nShape++] = new HLine(v[0], v[1], v[2]);
		}
		else if (type == 'c') {
			cin >> v[0] >> v[1] >> v[2];
			list[nShape++] = new Circle(v[0], v[1], v[2]);
		}
		else if (type == 'r') {
			cin >> v[0] >> v[1] >> v[2] >> v[3];
			list[nShape++] = new Rect(v[0], v[1], v[2], v[3]);
		}
		else if (type == 's') {
			cin >> v[0] >> v[1] >> v[2];
			list[nShape++] = new Square(v[0], v[1], v[2]);
		}
		else if (type == 'q') {
			break;
		}
		//me
		myCanvas.clear(". ");
		if (type == 'a') {
			for (int i = 0; i < nShape; i++) {
				list[i]->draw(myCanvas);
			}
		}
		else {
			list[nShape - 1]->draw(myCanvas);
		}
		//me end

		/*
		myCanvas.clear(". ");
		for (int i = 0; i < nShape; i++) {
			list[i]->draw(myCanvas);
		}
		*/
	}

	for (int i = 0; i < nShape; i++) {
		delete list[i];
	}
}