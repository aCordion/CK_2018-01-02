#pragma comment(lib, "ws2_32")	// ������ ���� ���̺귯��
#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <stdio.h>		//ǥ�� ����� ���
#include <WinSock2.h>	//�����켭 TCP/IP ��� ���α׷��� �����ϱ� ���� ���
#include <process.h>	//

#define DEBUG			// DEBUG Build
#define PORT_NUM 7777

#include "GameMap.h"
#include "util.h"
#include "MyCursor.h"
#include <Windows.h>
#include <time.h>
#include <conio.h>

#define MAPSIZEX	40
#define MAPSIZEY	20
#define MINES		50

struct key_data {
	//char dir;
	int x, y;
	bool doFlip;
};

struct StCData {
	int map[MAPSIZEY][MAPSIZEX];
	//char map[MAPSIZEY][MAPSIZEX];
};

void ErrorHandling(char * message);	//������ ���� ���ڿ��� ����ϱ� ���� �Լ�

unsigned WINAPI Client1_Thread(void *data);
unsigned WINAPI Client2_Thread(void *data);
unsigned WINAPI Client3_Thread(void *data);
unsigned WINAPI Client4_Thread(void *data);

#define MAX_PACKETLEN 256
#define MAX_CLIENTNUM 1		//������ Ŭ���̾�Ʈ �� 1~4 ����

int clientIdData[4];
int clientIdcurPos = 0;
bool clientIdAlready = false;
char rMessage[1000];

CGameMap game(MAPSIZEX, MAPSIZEY, MINES);
CMyCursor Player1(1, 1, MAPSIZEX, MAPSIZEY, true);
CMyCursor Player2(38, 1, MAPSIZEX, MAPSIZEY, true);
CMyCursor Player3(1, 18, MAPSIZEX, MAPSIZEY, true);
CMyCursor Player4(38, 18, MAPSIZEX, MAPSIZEY, true);

//char cDir[MAX_CLIENTNUM];
bool doFlip[MAX_CLIENTNUM];
struct sockaddr_in servAddr, clntAddr;	//IPv4 �ּ����� ����ü
SOCKET hServSock, hClntSock[4];	//���� ����
int clntAdrSize;	//�ּ��� ���̸� ������ ���� ����
struct key_data rData[MAX_CLIENTNUM];	//Ŭ���̾�Ʈ�� �ְ� ���� ������ ������ ����ü
struct StCData sMapData;

HANDLE h_Mutex;
HANDLE h_Thread[MAX_CLIENTNUM];


int main(int argc, char ** argv) {
	ScreenInit();	// ȭ�� �ʱ�ȭ
	//���α׷��� Ÿ��Ʋ �̸� ����
	system("title MineSweepers_server_win port(7777)");

	//HANDLE hThread;
	WSADATA wsaData;

	//���� ���� 2,2
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error!");	//���� ���� ��� �� ���α׷� ����(�����ʱ�ȭ)
	}
	//TCP;
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET) {
		ErrorHandling("socket() error");	//���� ���� ��� �� ���α׷� ����(���� ����)
	}

	//�ּ� ����ü �ʱ�ȭ
	ZeroMemory(&servAddr, sizeof(struct sockaddr_in));

	//������ �ּ� ����
	servAddr.sin_family = AF_INET;	//IPv4 ��������
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	//��� �ּҿ����� ������ �޾Ƶ���
	servAddr.sin_port = htons(PORT_NUM);	//��Ʈ �ּ� (PORT_NUM�� �� (7777))

	//bind
	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		ErrorHandling("bind() error");
	}

	if (SOCKET_ERROR == listen(hServSock, 5) == SOCKET_ERROR) {
		return 0;
	}

	ZeroMemory(&clntAddr, sizeof(struct sockaddr_in));

	h_Mutex = CreateMutex(NULL, FALSE, NULL);

	//���� �� �ʱ�ȭ
	srand((unsigned int)time(NULL));
	game.rstMap(MAPSIZEX, MAPSIZEY, MINES);


	//Ŭ���̾�Ʈ ������
	if (MAX_CLIENTNUM >= 1) {
		clntAdrSize = sizeof(clntAddr);
		hClntSock[0] = accept(hServSock, (SOCKADDR*)&clntAddr, &clntAdrSize);
		h_Thread[0] = (HANDLE)_beginthreadex(NULL, 0, Client1_Thread, NULL, 0, NULL);
	}
	if (MAX_CLIENTNUM >= 2) {
		clntAdrSize = sizeof(clntAddr);
		hClntSock[1] = accept(hServSock, (SOCKADDR*)&clntAddr, &clntAdrSize);
		h_Thread[1] = (HANDLE)_beginthreadex(NULL, 0, Client2_Thread, NULL, 0, NULL);
	}
	if (MAX_CLIENTNUM >= 3) {
		clntAdrSize = sizeof(clntAddr);
		hClntSock[2] = accept(hServSock, (SOCKADDR*)&clntAddr, &clntAdrSize);
		h_Thread[2] = (HANDLE)_beginthreadex(NULL, 0, Client3_Thread, NULL, 0, NULL);
	}
	if (MAX_CLIENTNUM == 4) {
		clntAdrSize = sizeof(clntAddr);
		hClntSock[3] = accept(hServSock, (SOCKADDR*)&clntAddr, &clntAdrSize);
		h_Thread[3] = (HANDLE)_beginthreadex(NULL, 0, Client4_Thread, NULL, 0, NULL);
	}


	//���� ����
	while (true) {
		memset((void*)&sMapData, 0x00, sizeof(sMapData));
		for (int y = 0; y < MAPSIZEY; y++) {
			for (int x = 0; x < MAPSIZEX; x++) {
				sMapData.map[y][x] = htonl(game.getMapNum(y, x));
				//sMapData.map[y][x] = game.getCharMap(y, x);
			}
		}for (int i = 0; i < MAX_CLIENTNUM; i++) {
			send(hClntSock[i], (char*)&sMapData, sizeof(sMapData), 0);
		}
		ScreenClear();	// ȭ�� �����
		game.draw();
		if (game.getCheckStatus() == 0) {
			Player1.draw();
			Player2.draw();
			Player3.draw();
			Player4.draw();
		}
		else {
			game.allTileOpen();
			switch (game.getCheckStatus()) {
			case 1:
				ScreenPrint(0, MAPSIZEY + 5, "< ���� >\n���ڸ� ������ ��� Ÿ���� �������ϴ�!\n");
				break;
			case 2:
				ScreenPrint(0, MAPSIZEY + 5, "< ���� >\n���ڰ� �����Ͽ����ϴ�.\n");
				break;
			}
		}
		ScreenPrint(0, MAPSIZEY + 1, "����Ű�� Ŀ�� �̵�, 'Space'Ű�� Ÿ�� Ȯ��");
		ScreenFlipping();	// ���� �ø�


	}
	closesocket(hServSock);
	for (int i = 0; i < MAX_CLIENTNUM; i++) {
		closesocket(hClntSock[i]);
	}
	CloseHandle(h_Mutex);
	WSACleanup();
	ScreenRelease();

	return 0;
}

int strLen[4];

unsigned WINAPI Client1_Thread(void *data) {
	Player1.setHide(false);
	while (true) {
		//WaitForSingleObject(h_Mutex, INFINITE);
			int recvLen;
			recvLen = recv(hClntSock[0], (char*)&rData[0], sizeof(rData[0]), 0);
			int x, y;
			x = htonl(rData[0].x);
			y = htonl(rData[0].y);
			doFlip[0] = rData[0].doFlip;
			Player1.setPos(x, y);

			if (doFlip[0]) {
				int x = Player1.getX();
				int y = Player1.getY();
				game.rcTileOpenner(x, y);
				doFlip[0] = false;
			}
		//ReleaseMutex(h_Mutex);
	}

	return 0;
}
unsigned WINAPI Client2_Thread(void *data) {
	Player2.setHide(false);
	while (true) {
		//WaitForSingleObject(h_Mutex, INFINITE);
		int recvLen;
		recvLen = recv(hClntSock[1], (char*)&rData[1], sizeof(rData[1]), 0);
		int x, y;
		x = htonl(rData[1].x);
		y = htonl(rData[1].y);
		doFlip[1] = rData[1].doFlip;
		Player2.setPos(x, y);

		if (doFlip[1]) {
			int x = Player2.getX();
			int y = Player2.getY();
			game.rcTileOpenner(x, y);
			doFlip[1] = false;
		}
		//ReleaseMutex(h_Mutex);
	}

	return 0;
}

unsigned WINAPI Client3_Thread(void *data) {
	Player3.setHide(false);
	while (true) {
		//WaitForSingleObject(h_Mutex, INFINITE);
		int recvLen;
		recvLen = recv(hClntSock[2], (char*)&rData[2], sizeof(rData[2]), 0);
		int x, y;
		x = htonl(rData[2].x);
		y = htonl(rData[2].y);
		doFlip[2] = rData[2].doFlip;
		Player3.setPos(x, y);

		if (doFlip[2]) {
			int x = Player3.getX();
			int y = Player3.getY();
			game.rcTileOpenner(x, y);
			doFlip[2] = false;
		}
		//ReleaseMutex(h_Mutex);
	}

	return 0;
}
unsigned WINAPI Client4_Thread(void *data) {
	Player4.setHide(false);
	while (true) {
		//WaitForSingleObject(h_Mutex, INFINITE);
		int recvLen;
		recvLen = recv(hClntSock[3], (char*)&rData[3], sizeof(rData[3]), 0);
		int x, y;
		x = htonl(rData[3].x);
		y = htonl(rData[3].y);
		doFlip[3] = rData[3].doFlip;
		Player4.setPos(x, y);

		if (doFlip[3]) {
			int x = Player4.getX();
			int y = Player4.getY();
			game.rcTileOpenner(x, y);
			doFlip[3] = false;
		}
		//ReleaseMutex(h_Mutex);
	}

	return 0;
}

void ErrorHandling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}