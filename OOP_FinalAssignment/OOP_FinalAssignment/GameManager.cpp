#include "GameManager.h"



GameManager::GameManager()
{
	m_BulletList = new BulletList();
	//bpGun = false;
	bDoorTriggered = false;
	keepPlay = true;
	isClear = false;
	targetHP = 20;
}


GameManager * GameManager::getInstance()
{
	static GameManager instance;
	return &instance;
}

GameManager::~GameManager()
{
	delete m_BulletList;
}

void GameManager::play()
{
	int curTime, oldTime;
	oldTime = clock();
	init();
	
	while (keepPlay && !isClear) {
		fpMove();
		fEShoot();
		update();
		fColCheck();
		draw();
		ScreenFlipping();

		while (true) {
			curTime = clock();
			if (curTime - oldTime > 33) {
				oldTime = curTime;
				break;
			}
		}
	}
	ScreenPrint(MAX_WIDTH - 8, (MAX_HEIGHT / 2) - 1, "###############################");
	ScreenPrint(MAX_WIDTH - 8, (MAX_HEIGHT / 2)    , "##                           ##");
	ScreenPrint(MAX_WIDTH - 8, (MAX_HEIGHT / 2) + 1, "###############################");
	if (!isClear) {
		ScreenPrint(MAX_WIDTH, MAX_HEIGHT / 2, "사망 - 게임 오버");
	}
	if (isClear) {
		ScreenPrint(MAX_WIDTH-4, MAX_HEIGHT / 2, "목표 사살 - 게임 클리어");
	}
	ScreenFlipping();
	Sleep(3000);
	ScreenRelease();
}


void GameManager::fpMove()
{
	//enum eTile { BLANK, WALL, ITEM };
	enum eTile { BLANK, WALL, DOOR };
	enum typeEnum { AMMO, HEART, KEY, GUN, BULLET };
	char* type[] = { "＠", "♥", "§", "￢", "⊙" };
	int pX = m_player.getX();
	int pY = m_player.getY();
	if (_kbhit()) {
		int nKey = _getch();
		switch (nKey) {
		case LEFT:
			pX--;
			m_player.setImg(2);
			break;
		case RIGHT:
			pX++;
			m_player.setImg(0);
			break;
		case UP:
			pY--;
			m_player.setImg(1);
			break;
		case DOWN:
			pY++;
			m_player.setImg(3);
			break;
		case SPACE:
			m_player.gunShoot();
			break;
		}
		if (m_map.Map(pX, pY) == DOOR) {
			return;
		}
		if ((m_map.Map(pX,pY) == BLANK/* || m_map.Map(pX, pY) == ITEM*/)) {
			m_player.setXY(pX, pY);
		}
	}
}

void GameManager::fEShoot()
{
#define ENEMY_SHOOT_DELAY 25
	static int delay = 0;
	delay++;
	if (delay >= ENEMY_SHOOT_DELAY) {
		delay = 0;
		int eNum = m_EnemyList.getCount();
		for (int i = 0; i < eNum; i++) {
			m_EnemyList.getObject(i)->gunShoot();
		}
	}
}

void GameManager::fColCheck()
{
	enum eTile { BLANK, WALL, ITEM };
	enum typeEnum { AMMO, HEART, KEY, GUN, BULLET };
	int iCount = m_ItemList.getCount();
	for (int i = 0; i < iCount; i++) {
		Objects *curItem = m_ItemList.getObject(i);
		if ((curItem->getX() == m_player.getX()) &&
			(curItem->getY() == m_player.getY()))
		{
			m_player.getItem(curItem->getType());
			if (curItem->getType() == KEY) {
				bDoorTriggered = true;
			}
			m_ItemList.remove(i);
			i--;
			iCount--;
			break;
		}
	}
	int bnum = m_BulletList->getCount();
	for (int bi = 0; bi < bnum; bi++) {
		Bullet *curBullet = m_BulletList->getObject(bi);
		int bX = curBullet->getX();
		int bY = curBullet->getY();
		int pX = m_player.getX();
		int pY = m_player.getY();
		bool isPlayers = curBullet->getPBullet();
		if ((bX == pX) && (bY == pY) && !isPlayers) {
			m_player.getDmg(curBullet->getDmg());
			m_BulletList->remove(bi);
			bi--;
			bnum--;
			if (m_player.getHP() <= 0) {
				keepPlay = false;//게임오버 처리
			}
			//break;
		}
		int eCount = m_EnemyList.getCount();
		for (int i = 0; i < eCount; i++) {
			Enemy *curEnemy = m_EnemyList.getObject(i);
			int eX = curEnemy->getX();
			int eY = curEnemy->getY();
			if ((bX == eX) && (bY == eY) && isPlayers) {
				curEnemy->getDmg(curBullet->getDmg());
				m_BulletList->remove(bi);
				bi--;
				bnum--;
				if (curEnemy->getHP() <= 0) {
					m_EnemyList.remove(i);
					i--;
					eCount--;
				}
				//break;
			}
		}
		if (m_map.Map(bX, bY) == 4) {
			m_BulletList->remove(bi);
			bi--;
			bnum--;
			targetHP--;
			if (targetHP <= 0) {
				isClear = true;
			}
		}
		if (m_map.Map(bX, bY) == WALL) {
			m_BulletList->remove(bi);
			bi--;
			bnum--;
			//break;
		}
	}
}

void GameManager::init()
{
	enum typeEnum { AMMO, HEART, KEY, GUN, BULLET };
	m_map.init();
	//Objects
	{
		Objects *ammo1 = new Objects(AMMO, 1, 2);
		m_ItemList.pushFront(ammo1);
		Objects *ammo2 = new Objects(AMMO, 36, 1);
		m_ItemList.pushFront(ammo2);
		Objects *ammo3 = new Objects(AMMO, 36, 2);
		m_ItemList.pushFront(ammo3);
		Objects *ammo4 = new Objects(AMMO, 36, 3);
		m_ItemList.pushFront(ammo4);
		Objects *ammo5 = new Objects(AMMO, 37, 1);
		m_ItemList.pushFront(ammo5);
		Objects *ammo6 = new Objects(AMMO, 37, 2);
		m_ItemList.pushFront(ammo6);
		Objects *ammo7 = new Objects(AMMO, 37, 3);
		m_ItemList.pushFront(ammo7);
		Objects *ammo8 = new Objects(AMMO, 38, 2);
		m_ItemList.pushFront(ammo8);
		Objects *ammo9 = new Objects(AMMO, 38, 3);
		m_ItemList.pushFront(ammo9);
		Objects *heart1 = new Objects(HEART, 17, 1);
		m_ItemList.pushFront(heart1);
		Objects *heart2 = new Objects(HEART, 18, 1);
		m_ItemList.pushFront(heart2);
		Objects *gun = new Objects(GUN, 1, 1);
		m_ItemList.pushFront(gun); 
		Objects *key = new Objects(KEY, 38, 1);
		m_ItemList.pushFront(key);
	}
	//Enemys
	{
		enum DIR { Right, Up, Left, Down };
		Enemy *inEnemy1 = new Enemy("T", 2, -1, 1, 4, Right);
		m_EnemyList.pushFront(inEnemy1);
		Enemy *inEnemy2 = new Enemy("T", 2, -1, 1, 9, Right);
		m_EnemyList.pushFront(inEnemy2);
		Enemy *inEnemy3 = new Enemy("T", 2, -1, 1, 11, Right);
		m_EnemyList.pushFront(inEnemy3);
		Enemy *inEnemy4 = new Enemy("T", 2, -1, 1, 14, Right);
		m_EnemyList.pushFront(inEnemy4);
		Enemy *inEnemy5 = new Enemy("T", 2, -1, 3, 1, Down);
		m_EnemyList.pushFront(inEnemy5);
		Enemy *inEnemy6 = new Enemy("T", 2, -1, 13, 6, Left);
		m_EnemyList.pushFront(inEnemy6);
		Enemy *inEnemy7 = new Enemy("T", 2, -1, 15, 8, Right);
		m_EnemyList.pushFront(inEnemy7);
		Enemy *inEnemy8 = new Enemy("T", 2, -1, 17, 16, Left);
		m_EnemyList.pushFront(inEnemy8);
		Enemy *inEnemy9 = new Enemy("T", 2, -1, 28, 11, Left);
		m_EnemyList.pushFront(inEnemy9);
		Enemy *inEnemy10 = new Enemy("T", 2, -1, 28, 16, Left);
		m_EnemyList.pushFront(inEnemy10);
		Enemy *inEnemy11 = new Enemy("T", 2, -1, 29, 1, Down);
		m_EnemyList.pushFront(inEnemy11);
		Enemy *inEnemy12 = new Enemy("T", 2, -1, 31, 1, Down);
		m_EnemyList.pushFront(inEnemy12);
		Enemy *inEnemy13 = new Enemy("T", 2, -1, 33, 1, Down);
		m_EnemyList.pushFront(inEnemy13);
		Enemy *inEnemy14 = new Enemy("T", 2, -1, 35, 1, Down);
		m_EnemyList.pushFront(inEnemy14);
		Enemy *inEnemy15 = new Enemy("T", 2, -1, 38, 4, Left);
		m_EnemyList.pushFront(inEnemy15);
		Enemy *inEnemy16 = new Enemy("T", 2, -1, 38, 6, Left);
		m_EnemyList.pushFront(inEnemy16);
		Enemy *inEnemy17 = new Enemy("T", 2, -1, 38, 8, Left);
		m_EnemyList.pushFront(inEnemy17);
	}
}

void GameManager::fInterface()
{
	char str[20];
	int itemp;

	ScreenPrint(MAX_WIDTH * 2, 0, "               <게임 TIP>");
	ScreenPrint(MAX_WIDTH * 2, 1, " ======================================");
	ScreenPrint(MAX_WIDTH * 2, 3, "    ▲▼◀▶ == 벽 고정형 터렛 (HP 2)");
	ScreenPrint(MAX_WIDTH * 2, 4, "      ＠ == 탄약+5	￢ == 총");
	ScreenPrint(MAX_WIDTH * 2, 5, "      ■ == 벽		♥ == 체력+1");
	ScreenPrint(MAX_WIDTH * 2, 6, "      ▩ == 잠긴 문	§ == 열쇠");
	ScreenPrint(MAX_WIDTH * 2, 7, "      ⊙ == 발사된 탄환(HP - 1)"); 
	ScreenPrint(MAX_WIDTH * 2, 8, "      화살표 == 플레이어");
	if (bDoorTriggered) {
		itemp = targetHP;
		itoa(itemp, str, 10);
	ScreenPrint(MAX_WIDTH * 2, 11, "               <Target>");
	ScreenPrint(MAX_WIDTH * 2, 12, "              ▒▒▒▒▒ ");
	ScreenPrint(MAX_WIDTH * 2, 13, "              ▒  ▒  ▒ ");
	ScreenPrint(MAX_WIDTH * 2, 14, "              ▒▒▒▒▒ ");
	ScreenPrint(MAX_WIDTH * 2, 15, "              ▒▒  ▒▒ ");
	ScreenPrint(MAX_WIDTH * 2, 16, "              ▒  ▒  ▒ ");
	ScreenPrint(MAX_WIDTH * 2, 17, "              ▒▒▒▒▒ ");
	ScreenPrint(MAX_WIDTH * 2, 18, "               <HP    >");
	ScreenPrint((MAX_WIDTH+10) * 2, 18, str);
	}
	
	itemp = m_player.getHP();
	itoa(itemp, str, 10);
	ScreenPrint(2 * 2, MAX_HEIGHT + 1, "H 체력 =     ");
	ScreenPrint(7 * 2, MAX_HEIGHT + 1, str);
	itemp = m_player.getIBullet();
	itoa(itemp, str, 10);
	ScreenPrint(2 * 2, MAX_HEIGHT + 2, "B 탄약 =     ");
	ScreenPrint(7 * 2, MAX_HEIGHT + 2, str);
	itemp = m_player.getX();
	itoa(itemp, str, 10);
	ScreenPrint(12 * 2, MAX_HEIGHT + 1, "X 좌표 =     ");
	ScreenPrint(17 * 2, MAX_HEIGHT + 1, str);
	itemp = m_player.getY();
	itoa(itemp, str, 10);
	ScreenPrint(12 * 2, MAX_HEIGHT + 2, "Y 좌표 =     ");
	ScreenPrint(17 * 2, MAX_HEIGHT + 2, str);
	ScreenPrint(0, MAX_HEIGHT + 5, "↑↓←→ = 이동,  Space = 총 발사");
	
}

void GameManager::update()
{
	int bnum = m_BulletList->getCount();
	for (int bi = 0; bi < bnum; bi++) {
		m_BulletList->getObject(bi)->move();
	}
	if (bDoorTriggered) {
		m_map.Map(29, 17) = 0;
		m_map.Map(29, 18) = 0;
		for (int x = 30; x < 39; x++) {
			for (int y = 11; y < 19; y++) {
				m_map.Map(x, y) = 0;
			}
		}//34,12 to 38,17
		for (int x = 34; x < 39; x++) {
			for (int y = 12; y < 18; y++) {
				m_map.Map(x, y) = 4;
			}
		}
		m_map.Map(35, 13) = 0;
		m_map.Map(37, 13) = 0;
		m_map.Map(36, 15) = 0;
		m_map.Map(35, 16) = 0;
		m_map.Map(37, 16) = 0;
	}
}

void GameManager::draw()
{
	m_map.draw();
	int inum = m_ItemList.getCount();
	for (int i = 0; i < inum; i++) {
		m_ItemList.getObject(i)->draw();
	}
	int bnum = m_BulletList->getCount();
	for (int i = 0; i < bnum; i++) {
		m_BulletList->getObject(i)->draw();
	}
	int eNum = m_EnemyList.getCount();
	for (int i = 0; i < eNum; i++) {
		m_EnemyList.getObject(i)->draw();
	}
	m_player.draw();
	fInterface();
}
