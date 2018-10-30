#include "Tile.h"
#include "util.h"


CTile::CTile()
{
}

CTile::~CTile()
{
}

void CTile::draw()
{
	//Tile List
	{
		//imgs[0] = Blank
		//imgs[1] = ScreenBorder
	}
	char *imgs[] = { "  " ,"бс" };

	ScreenPrint(m_x * 2, m_y, imgs[m_num]);
	
}
