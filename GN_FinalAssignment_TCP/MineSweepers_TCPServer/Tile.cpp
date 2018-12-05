#include "Tile.h"
#include "util.h"


CTile::CTile()
{
	m_bOpen = false;
}

CTile::~CTile()
{
}

char CTile::getCNum()
{
	char imgs[] = { '¡Û','¨ç','¨è','¨é','¨ê','¨ë','¨ì','¨í','¨î','¡Ù' };

	return imgs[m_num];
}

void CTile::draw()
{
	char *imgs[] = { "¡Û","¨ç","¨è","¨é","¨ê","¨ë","¨ì","¨í","¨î","¡Ù" };
	//	char *mineImg = "¡Ù";

	if (!m_bOpen){
		ScreenPrint(m_x * 2, m_y, "¡à");
}
	else {
		ScreenPrint(m_x * 2, m_y, imgs[m_num]);
	}
}

