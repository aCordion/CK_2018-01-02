#include "Tile.h"
#include "util.h"


CTile::CTile()
{
	m_bOpen = false;
}

CTile::~CTile()
{
}

void CTile::draw()
{
	char *imgs[] = { "��","��","��","��","��","��","��","��","��","��" };
	//	char *mineImg = "��";

	if (!m_bOpen){
		ScreenPrint(m_x * 2, m_y, "��");
}
	else {
		ScreenPrint(m_x * 2, m_y, imgs[m_num]);
	}
}
