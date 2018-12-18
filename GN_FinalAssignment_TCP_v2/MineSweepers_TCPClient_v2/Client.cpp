//201813113 ���ϼ�
#pragma comment(lib, "ws2_32")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <process.h>

#include <conio.h>
#include "util.h"
#include "GameMap.h"
#include "MyCursor.h"

int MAX_CLIENTNUM;

#define IP_NUM "127.0.0.1"	//IP
#define PORT_NUM 7777		//port

#define MAPSIZEX	40
#define MAPSIZEY	20


struct key_data {
	//char dir;		//����
	int x, y;		//��ǥ
	bool doFlip;	//�ø�
};

struct pos_data {
	int x1, x2, x3, x4;
	int y1, y2, y3, y4;
};

struct StCData {
	int map[MAPSIZEY][MAPSIZEX];
	int cliNum;
	//char map[MAPSIZEY][MAPSIZEX];
};
//   *imgs[] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10  };
char *imgs[] = { "��","��","��","��","��","��","��","��","��","��","��" };

unsigned WINAPI getCursor(void *data);
void cursorCon();
HANDLE h_getCursor;
CGameMap map(MAPSIZEX,MAPSIZEY,0);
CMyCursor Cursor(1, 1, 40, 20, true);
CMyCursor Cursor1(1, 1, 40, 20, true);
CMyCursor Cursor2(1, 1, 40, 20, true);
CMyCursor Cursor3(1, 1, 40, 20, true);
CMyCursor Cursor4(1, 1, 40, 20, true);

SOCKET sockfd;	//���� ����
int otherX[4];
int otherY[4];
struct key_data sData;
struct key_data rData;
struct pos_data rpData;

int main(int argc, char ** argv) {
	ScreenInit();	// ȭ�� �ʱ�ȭ
	//���α׷��� Ÿ��Ʋ �̸� ����
	system("title MineSweepers_client_win 127.0.0.1");

	
	WSADATA wsaData;	//���� �ʱ�ȭ
	struct sockaddr_in servAdr;	//IPv4 �ּ����� ����ü
										
	struct StCData rMapData;
	
	//if (argc != 2) {
	//	printf("Usage : %s [ip address]\n", argv[0]);
	//	return 1;	//main�Լ� ��ȯ
	//}

	// ���� ���� �ʱ�ȭ�� �����ϴ� ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
		return 1;	//main�Լ� ��ȯ
	}

	//IPv4 ��������, TCP ����� ����
	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	//���� ���� ����
	if (sockfd == INVALID_SOCKET) {
		return -1;
	}

	//�ּ� ����ü �ʱ�ȭ
	memset((void*)&servAdr, 0x00, sizeof(servAdr));

	//�ּ� ����
	servAdr.sin_family = AF_INET;	//IPv4 ��������
	//servAdr.sin_addr.s_addr = inet_addr(argv[1]);	//�ڽ��� IP�ּҸ� �Ҵ�(main�Լ� ����μ�)
	servAdr.sin_addr.s_addr = inet_addr(IP_NUM); //IP_NUM("127.0.0.1")
	servAdr.sin_port = htons(PORT_NUM);	//PORT_NUM(7777)

    //connect
	if (connect(sockfd, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR) {
		return -1;
	}

	//�� ����ȭ
	recv(sockfd, (char*)&rMapData, sizeof(rMapData), 0);
	for (int y = 0; y < MAPSIZEY; y++) {
		for (int x = 0; x < MAPSIZEX; x++) {
			int n = htonl(rMapData.map[y][x]);
			map.setMap(x, y, n);
		}
	}
	MAX_CLIENTNUM = htonl(rMapData.cliNum);
	if (MAX_CLIENTNUM >= 1) {
		Cursor1.setHide(false);
	}
	if (MAX_CLIENTNUM >= 2) {
		Cursor2.setHide(false);
	}
	if (MAX_CLIENTNUM >= 3) {
		Cursor3.setHide(false);
	}
	if (MAX_CLIENTNUM >= 4) {
		Cursor4.setHide(false);
	}

	h_getCursor = (HANDLE)_beginthreadex(NULL, 0, getCursor, NULL, 0, NULL);
	//���� ����
	while (true) {
		ScreenClear();	// ȭ�� �����
		map.draw();
		if (map.getCheckStatus() == 0) {
			cursorCon();
			//Cursor.draw();
			if (MAX_CLIENTNUM >= 1) {
				Cursor1.setPos(otherX[0], otherY[0]);
				Cursor1.draw();
			}
			if (MAX_CLIENTNUM >= 2) {
				Cursor2.setPos(otherX[1], otherY[1]);
				Cursor2.draw();
			}
			if (MAX_CLIENTNUM >= 3) {
				Cursor3.setPos(otherX[2], otherY[2]);
				Cursor3.draw();
			}
			if (MAX_CLIENTNUM >= 4) {
				Cursor4.setPos(otherX[3], otherY[3]);
				Cursor4.draw();
			}
			/*for (int i = 0; i < MAX_CLIENTNUM; i++) {
				ScreenPrint(otherX[i] * 2, otherY[i], "��");
			}*/
		}
		else {
			map.allTileOpen();
			switch (map.getCheckStatus()) {
			case 1:
				ScreenPrint(0, MAPSIZEY + 5, "< ���� >\n���ڸ� ������ ��� Ÿ���� �������ϴ�!\n");
				break;
			case 2:
				ScreenPrint(0, MAPSIZEY + 5, "< ���� >\n���ڰ� �����Ͽ����ϴ�.\n");
				break;
			}
		}

		ScreenPrint(0, MAPSIZEY + 1, "����Ű�� Ŀ�� �̵�, 'Space'Ű�� Ÿ�� Ȯ��");
		ScreenFlipping();	// ���� ���
	}
	closesocket(sockfd);
	WSACleanup();
	ScreenRelease();
	return 0;
}

void cursorCon(){
	memset((void*)&sData, 0x00, sizeof(sData));
	if (_kbhit()) {
		int inKey = _getch();
		switch (inKey) {
		case UP:
			Cursor.goUp();
			break;
		case DOWN:
			Cursor.goDown();
			break;
		case LEFT:
			Cursor.goLeft();
			break;
		case RIGHT:
			Cursor.goRight();
			break;
		case SPACE:
			int x = Cursor.getX();
			int y = Cursor.getY();
			map.rcTileOpenner(x, y);
			sData.doFlip = (char)inKey;
			break;
		}
		sData.x = htonl(Cursor.getX());
		sData.y = htonl(Cursor.getY());

		int dataLen = sizeof(sData);
		send(sockfd, (char*)&sData, dataLen, 0);
	}
}

unsigned WINAPI getCursor(void * data)
{
	while (true) {
		recv(sockfd, (char*)&rData, sizeof(rData), 0);
		recv(sockfd, (char*)&rpData, sizeof(rpData), 0);
		int x = htonl(rData.x);
		int y = htonl(rData.y);

		int i = 0;
		if ((i == 0) && (i < MAX_CLIENTNUM)) {
			otherX[i] = htonl(rpData.x1);
			otherY[i] = htonl(rpData.y1);
			i++;
		}
		if ((i == 1) && (i < MAX_CLIENTNUM)) {
			otherX[i] = htonl(rpData.x2);
			otherY[i] = htonl(rpData.y2);
			i++;
		}
		if ((i == 2) && (i < MAX_CLIENTNUM)) {
			otherX[i] = htonl(rpData.x3);
			otherY[i] = htonl(rpData.y3);
			i++;
		}
		if ((i == 3) && (i < MAX_CLIENTNUM)) {
			otherX[i] = htonl(rpData.x4);
			otherY[i] = htonl(rpData.y4);
		}
		//map.setTile(x, y, rData.doFlip);
		if (rData.doFlip) {
			map.rcTileOpenner(x, y);
			rData.doFlip = false;
		}
		//ScreenFlipping();	// ���� ���
	}
	return 0;
}
