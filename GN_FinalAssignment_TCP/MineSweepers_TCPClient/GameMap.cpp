#include "GameMap.h"

enum etiles { none = 0, mine = 9 };
enum eCheckStatus { keep = 0, win = 1, fail = 2 };

CGameMap::~CGameMap()
{

}

CGameMap::CGameMap(int w, int h, int n)
{
	checkStatus = keep;
	nLeftTiles = ((w * h) - n);
	nOpenTiles = 0;
	m_map = nullptr;
	setMap(w, h, n);
}

void CGameMap::initMap()
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			m_map[y][x].setTile(x, y, 0);
		}
	}
}

void CGameMap::initMap(CGameMap & map)
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			//m_map[y][x].setTile(x, y, map.getMapNum[y][x]);
		}
	}
}

#include <Windows.h>
void CGameMap::setMines()
{
	int curX, curY;
	for (int i = 0; i < m_mineNum; i++) {
		do {
			curX = rand() % m_width;
			curY = rand() % m_height;
		} while (m_map[curY][curX].getNum() == mine);
		m_map[curY][curX].setTile(curX, curY, mine);
		updateTile(curX, curY);
	}
}

void CGameMap::setMap(int w, int h, int n)
{

	if (m_map) {
		for (int i = 0; i < m_height; i++) {
			delete[] m_map[i];
		}
		delete[] m_map;
		m_map = nullptr;
	}

	m_width = w;
	m_height = h;
	m_mineNum = n;

	m_map = new CTile *[m_height];
	for (int i = 0; i < m_height; i++)
		m_map[i] = new CTile[m_width];
	initMap();
	setMines();
}

void CGameMap::updateTile(int x, int y)
{
	int curX, curY;
	for (int ty = -1; ty <= 1; ty++) {
		for (int tx = -1; tx <= 1; tx++) {
			curX = x + tx;
			curY = y + ty;
			if (curX < 0 || curY < 0 ||
				curX > m_width - 1 || curY>m_height - 1 ||
				m_map[curY][curX].getNum() == mine)
				continue;
			int tileNum = m_map[curY][curX].getNum();
			m_map[curY][curX].setTile(curX, curY, tileNum + 1);
		}
	}
}

void CGameMap::setTile(int x, int y, bool bOpen)
{
	m_map[y][x].setOpen(bOpen);
}

void CGameMap::draw()
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			m_map[y][x].draw();
		}
	}
}

char CGameMap::getCharMap(int x, int y)
{
	return m_map[y][x].getCNum();
}

int CGameMap::getMapNum(int y, int x)
{
	return m_map[y][x].getNum();
}

void CGameMap::rcTileOpenner(int x, int y)
{
	if (x > m_width-1 || y > m_height-1 || x < 0 || y < 0) {	//맵의 크기좌표를 벗어날 경우 반환
		return;
	}
	if (m_map[y][x].isOpen() == false) {	//맵의 해당 좌표가 열려있지 않을 경우
		setTile(x, y, true);				//맵의 해당 좌표를 염
		nOpenTiles++;						//연 타일 수 만큼 카운트
		if (nLeftTiles == nOpenTiles) {
			checkStatus = win;
		}
		if (m_map[y][x].getNum() == mine) {	//연 좌표가 지뢰일 경우 상태값(checkStatus)에 실패(2 == fail))를 대입
			checkStatus = fail;
		}
		//연 좌표가 비어있을(8방향으로 1칸 범위에 지뢰가 없을)경우 재귀함
		if (m_map[y][x].getNum() == none) {	
			rcTileOpenner(x - 1, y - 1);
			rcTileOpenner(x - 1, y);
			rcTileOpenner(x - 1, y + 1);
			rcTileOpenner(x, y - 1);
			rcTileOpenner(x, y + 1);
			rcTileOpenner(x + 1, y - 1);
			rcTileOpenner(x + 1, y);
			rcTileOpenner(x + 1, y + 1);
		}
	}
}

void CGameMap::allTileOpen()
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			m_map[y][x].setOpen(true);
		}
	}
}

void CGameMap::rstMap(int w, int h, int n)
{
	setCheckStatus(keep);
	nLeftTiles = ((w * h) - n );
	nOpenTiles = 0;
	setMap(w, h, n);
}
