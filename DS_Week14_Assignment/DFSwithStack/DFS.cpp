#include "DFS.h"



DFS::DFS(pos maxPos, pos from, pos to)
{
	m_maxX = maxPos.x;
	m_maxY = maxPos.y;
	m_rIndex = 0;
	m_curPos = from;
	m_route = new pos[m_maxX * m_maxY];
	m_toPos = to;
	m_fromPos = from;
	m_copyMap = new int *[m_maxY];
	m_visitMap = new bool *[m_maxY];
	for (int y = 0; y < m_maxY; y++) {
		m_copyMap[y] = new int[m_maxX];
		m_visitMap[y] = new bool[m_maxX];
	}
	for (int y = 0; y < m_maxY; y++) {
		for (int x = 0; x < m_maxX; x++) {
			m_visitMap[y][x] = false;
		}
	}
	m_visitStack.push(from);
	m_route[m_rIndex++] = from;
	m_visitMap[from.y][from.x] = true;
}


DFS::~DFS()
{
	for (int y = 0; y < m_maxY; y++) {
		delete[] m_copyMap[y];
		delete[] m_visitMap[y];
	}
	delete[] m_copyMap;
	delete[] m_visitMap;
	delete[] m_route;
}

void DFS::mapCopy(int y, int x, int data)
{
	m_copyMap[y][x] = data;
}

bool DFS::Find()
{
	for (int y = 0; y < m_maxY; y++) {
		for (int x = 0; x < m_maxX; x++) {
			if (m_copyMap[y][x] != 0) {
				m_visitMap[y][x] = true;
			}
		}
	}
	while (!m_visitStack.isEmpty() && (m_toPos != m_visitStack.getTop())) {
		//m_curPos = m_visitStack.getTop();
		if (checkVisited()) {
			m_visitStack.pop();
			m_curPos = m_visitStack.getTop();
			m_route[m_rIndex++] = m_curPos;
		}
		else {
			chooseNext();
		}
	}
	if (m_visitStack.isEmpty()) {
		cout << "목표까지의 길이 존재하지 않습니다!" << endl;
		return false;
	}
	else {
		cout << endl << "탐색 시작 지점 " << m_fromPos << " 부터 " << "탐색 목표 지점 " << m_toPos << "까지..." << endl;
		cout << "목표까지의 길이 존재합니다." << endl;
		cout << "맵 상의 탐색 경로." << endl;
		drawRouteView();
		cout << "좌표 상의 탐색 경로." << endl;
		drawRoutePos();
		return true;
	}
}

bool DFS::checkVisited()
{
	if (m_visitMap[m_curPos.y][m_curPos.x + 1] == true && m_visitMap[m_curPos.y - 1][m_curPos.x] == true &&
		m_visitMap[m_curPos.y][m_curPos.x - 1] == true && m_visitMap[m_curPos.y + 1][m_curPos.x] == true) {
		return true;
	}
	else {
		return false;
	}
}

void DFS::chooseNext()
{
	if (m_visitMap[m_curPos.y][m_curPos.x + 1] == false) {
		m_curPos.x++;
	}
	else if (m_visitMap[m_curPos.y - 1][m_curPos.x] == false) {
		m_curPos.y--;
	}
	else if (m_visitMap[m_curPos.y][m_curPos.x - 1] == false) {
		m_curPos.x--;
	}
	else if (m_visitMap[m_curPos.y + 1][m_curPos.x] == false) {
		m_curPos.y++;
	}
	m_route[m_rIndex++] = m_curPos;
	m_visitStack.push(m_curPos);
	m_visitMap[m_curPos.y][m_curPos.x] = true;
}

void DFS::TESTDRAW()
{
	cout << "메인의 맵을 DFS객체로 복사한 결과" << endl;
	for (int y = 0; y < m_maxY; y++) {
		for (int x = 0; x < m_maxX; x++) {
			cout <<m_copyMap[y][x]; 
		}
		cout << endl;
	}
	system("pause");
	for (int y = 0; y < m_maxY; y++) {
		for (int x = 0; x < m_maxX; x++) {
			if (m_visitMap[y][x]) {
				cout << "■";
			}
			else {
				cout << "□";
			}
		}
		cout << endl;
	}
	system("pause");
	
}

void DFS::drawRoutePos()
{
	for (int i = 0; i < m_rIndex; i++) {
		cout << m_route[i] << ", ";
		if (i != 0 && (i % 10 == 0)) {
			cout << endl;
		}
	}
}

void DFS::drawRouteView()
{
	for (int i = 0; i < m_rIndex; i++) {
		m_copyMap[m_route[i].y][m_route[i].x] = 2;
	}

	for (int y = 0; y < m_maxY; y++) {
		for (int x = 0; x < m_maxX; x++) {
			if (m_copyMap[y][x] == 1) {
				cout << "■";
			}
			else if (m_copyMap[y][x] == 0) {
				cout << "  ";
			}
			else {
				cout << "▒";
			}
		}
		cout << endl;
	}
}
