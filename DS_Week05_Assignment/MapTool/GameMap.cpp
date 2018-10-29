#include "GameMap.h"
#include "util.h"

//0		1		2
enum TileStyle { BLANK, WALL, OBJECT };
char *tileImg[] = { " ", "■", "☆" };

CGameMap::CGameMap()
{
	m_width = 40;
	m_height = 20;
	m_map = new int *[m_height];
	for (int i = 0; i < m_height; i++) {
		m_map[i] = new int[m_width];
	}
	initMap();
}

CGameMap::~CGameMap()
{
}


void CGameMap::initMap()
{
	TileStyle t;
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			t = (x == 0 || y == 0 || x == m_width - 1 || y == m_height - 1) ? WALL : BLANK;
			//setTile(x, y, t);
			m_map[y][x] = t;
		}
	}
}

void CGameMap::draw()
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			ScreenPrint(x * 2, y, tileImg[m_map[y][x]]);
		}
	}
	ScreenPrint(0, m_height, "W,A,S,D 혹은 방향키로 커서 이동, Z 벽 설치, X 오브젝트 설치, C 지우기");
}

void CGameMap::actDraw(int x, int y, int KEY)
{
	//setTile(x, y, OBJECT);
	switch (KEY) {
	case KEY_Z:
	case KEY_z:
		m_map[y][x] = WALL;
		break;

	case KEY_X: 
	case KEY_x:
		m_map[y][x] = OBJECT;
		break;

	case KEY_C:
	case KEY_c:
		m_map[y][x] = BLANK;
		break;
	}
}

void CGameMap::curStatDraw(int x, int y)
{
	switch (m_map[y][x]) {
	case BLANK:
		ScreenPrint(0, m_height+1, "현재 커서가 위치한 좌표는 비어있습니다.         ");
		break;
	case WALL:
		ScreenPrint(0, m_height+1, "현재 커서가 위치한 좌표에는 벽이 있습니다.      ");
		break;
	case OBJECT:
		ScreenPrint(0, m_height+1, "현재 커서가 위치한 좌표에는 오브젝트가 있습니다.");
		break;
	}
}
