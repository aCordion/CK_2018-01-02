#include "Shape.h"



Shape::Shape()
{
}


Shape::~Shape()
{
	cout << "Shape ¼Ò¸êÀÚ È£Ãâ ......" << endl;
}

void Shape::draw(CCanvas & canvas, string color)
{
	canvas.draw(p.x, p.y, color);
}

void Line::draw(CCanvas & canvas, string color)
{
	int len = Max(Abs(q.x - p.x), Abs(q.y - p.y));
	double x = p.x, y = p.y;
	double dx = (q.x - p.x) / (double)len, dy = (q.y - p.y) / (double)len;
	for (int i = 0; i <= len; i++) {
		canvas.draw(Round(x), Round(y), color);
		x += dx;
		y += dy;
	}
}

void Rect::draw(CCanvas & canvas, string color)
{
	for (int i = p.x; i <= p.x + w; i++) {
		canvas.draw(i, p.y, color);
		canvas.draw(i, p.y + h, color);
	}
	for (int i = p.y; i <= p.y + h; i++) {
		canvas.draw(p.x, i, color);
		canvas.draw(p.x + w, i, color);
	}
}

void Circle::draw(CCanvas & canvas, string color)
{
	Line(p.x, p.y, p.x, p.y + r).draw(canvas, color);
	Line(p.x, p.y, p.x, p.y - r).draw(canvas, color);
	Line(p.x, p.y, p.x + r, p.y).draw(canvas, color);
	Line(p.x, p.y, p.x - r, p.y).draw(canvas, color);
}
