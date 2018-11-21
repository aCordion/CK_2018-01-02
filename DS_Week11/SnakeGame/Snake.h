#pragma once

class CObjectList;
typedef int DIR;	//뱀의 이동 방향 설정

class CSnake
{
	CObjectList *m_tailList;	//뱀의 꼬리들 관리
	DIR m_dir;	//뱀의 이동 방향

public:
	~CSnake();
	CSnake(CObjectList *list);
	DIR getDir() { return m_dir; }
	CObjectList *getTails() { return m_tailList; }

	void setDir(DIR d) { m_dir = d; }

	void update();
	void draw();
};

