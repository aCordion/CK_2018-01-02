#pragma comment(lib, "ws2_32")	// ������ ���� ���̺귯��
#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <stdio.h>		//ǥ�� ����� ���
#include <WinSock2.h>	//�����켭 TCP/IP ��� ���α׷��� �����ϱ� ���� ���

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
	char dir;
	bool doFlip;
};

struct StCData {
	int map[MAPSIZEY][MAPSIZEX];
	//char map[MAPSIZEY][MAPSIZEX];
};

int getNum(int MAX);
DWORD WINAPI t_func(void *data);

CGameMap game(MAPSIZEX, MAPSIZEY, MINES);
CMyCursor Player1(1, 1, MAPSIZEX, MAPSIZEY, false);
CMyCursor Player2(38, 1, MAPSIZEX, MAPSIZEY, false);
CMyCursor Player3(1, 18, MAPSIZEX, MAPSIZEY, false);
CMyCursor Player4(38, 18, MAPSIZEX, MAPSIZEY, false);
char cDir;
bool doFlip;
struct sockaddr_in addr, cliaddr;	//IPv4 �ּ����� ����ü
struct key_data rData;	//Ŭ���̾�Ʈ�� �ְ� ���� ������ ������ ����ü
struct StCData sMapData;

int main(int argc, char ** argv) {
	ScreenInit();	// ȭ�� �ʱ�ȭ
	//���α׷��� Ÿ��Ʋ �̸� ����
	system("title MineSweepers_server_win port(7777)");

	SOCKET sockfd;	//���� ����
	int addrlen;	//�ּ��� ���̸� ������ ���� ����

	WSADATA wsaData;	//���� �ʱ�ȭ

	//���� ���� ���� 2.2�� �ʱ�ȭ���� ������ �ƴ� ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
		return 1;	//main�Լ� ��ȯ
	}

	//���� ���� ���� ������ ������ ���
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		return 1;	//main�Լ� ��ȯ
	}

	//���� �ּҸ� 0���� ���� �ּ��� ���̸�ŭ ����
	memset((void*)&addr, 0x00, sizeof(addr));

	//������ �ּ� ����
	addr.sin_family = AF_INET;	//���� �ּҴ� IPv4 ��������
	addr.sin_addr.s_addr = htonl(INADDR_ANY);	//��� �ּҿ����� ������ �޾Ƶ���
	addr.sin_port = htons(PORT_NUM);	//��Ʈ �ּ� (��� PORT_NUM�� �� (7777))

	//�ּ��� ũ��
	addrlen = sizeof(addr);

	//���� ������ ����Ʈ���� ��Ʈ�� IP�� ���� ���� ������ ���
	if (bind(sockfd, (struct sockaddr *)&addr, addrlen) == -1) {
		return 1;	//main�Լ� ��ȯ
	}
	srand((unsigned int)time(NULL));
	

	clock_t oldTime, curTime;
	oldTime = clock();

	while (true) {
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
		//ScreenPrint(0, MAPSIZEY + 2, "'R'Ű�� ���� �ٽ� ���� �մϴ�.\n'ESC'Ű�� ���� �����մϴ�.");
		ScreenFlipping();	// ȭ�鿡 �����ֱ�


	}
	{
	//game.rstMap(MAPSIZEX, MAPSIZEY, MINES);

	//// game logic
	//while (true) {

	//	// draw call
	//	ScreenClear();	// ȭ�� �����
	//	game.draw();
	//	

	//	if (game.getCheckStatus() == 0) {
	//		Player1.draw();
	//		Player2.draw();
	//		Player3.draw();
	//		Player4.draw();
	//	}
	//	//		if (game.getCheckStatus() != 0) {
	//	else {
	//		game.allTileOpen();
	//		switch (game.getCheckStatus()) {
	//		case 1:
	//			ScreenPrint(0, MAPSIZEY + 5, "< ���� >\n���ڸ� ������ ��� Ÿ���� �������ϴ�!\n");
	//			break;
	//		case 2:
	//			ScreenPrint(0, MAPSIZEY + 5, "< ���� >\n���ڰ� �����Ͽ����ϴ�.\n");
	//			break;
	//		}
	//	}
	//	ScreenPrint(0, MAPSIZEY + 1, "����Ű�� Ŀ�� �̵�, 'Space'Ű�� Ÿ�� Ȯ��");
	//	//ScreenPrint(0, MAPSIZEY + 2, "'R'Ű�� ���� �ٽ� ���� �մϴ�.\n'ESC'Ű�� ���� �����մϴ�.");
	//	ScreenFlipping();	// ȭ�鿡 �����ֱ�

	//	memset((void*)&sMapData, 0x00, sizeof(sMapData));
	//	for (int y = 0; y < MAPSIZEY; y++) {
	//		for (int x = 0; x < MAPSIZEX; x++) {
	//			sMapData.map[y][x] = htonl(game.getMapNum(y, x));
	//		}
	//	}
	//	//Ŭ���̾�Ʈ �ּ��� ũ��
	//	addrlen = sizeof(cliaddr);
	//	//Ŭ���̾�Ʈ�� ���� rdata(cal_data ����ü)�� ���� ����
	//	recvfrom(sockfd, (char*)&rData, sizeof(rData), 0, (struct sockaddr*)&cliaddr, &addrlen);
	//	addrlen = sizeof(cliaddr);
	//	sendto(sockfd, (char*)&sMapData, sizeof(sMapData), 0, (struct sockaddr*)&cliaddr, addrlen);

	//	
	//	// Ű���� �Է� ó��
	//	cDir = rData.dir;
	//	doFlip = rData.doFlip;
	//	
	//	switch (cDir) {
	//	case UP:
	//		Player1.goUp();
	//		break;
	//	case DOWN:
	//		Player1.goDown();
	//		break;
	//	case LEFT:
	//		Player1.goLeft();
	//		break;
	//	case RIGHT:
	//		Player1.goRight();
	//		break;
	//	}
	//	if (doFlip) {
	//		int x = Player1.getX();
	//		int y = Player1.getY();
	//		game.rcTileOpenner(x, y);
	//		doFlip = false;
	//	}
	//				
	//	//while (1) {
	//	//	curTime = clock();
	//	//	if (curTime - oldTime > 33) {
	//	//		oldTime = curTime;
	//	//		break;
	//	//	}
	//	//}
	//}
}
	closesocket(sockfd);	//������ ����
	WSACleanup();	//���� �ʱ�ȭ
	ScreenRelease();	//ȭ�� ����
}
#define MAX_PACKETLEN 256
#define MAX_CLIENTNUM 4
int clientNum[4];
int clientCurCount = 0;
DWORD WINAPI t_func(void *data) {

	SOCKET sockfd = (SOCKET)data;
	int readn, writen;
	int addrlen;
	struct sockaddr_in sock_addr;
	char szReceiveBuffer[MAX_PACKETLEN];

	printf("Thread Start : %d\n", GetCurrentThreadId());
	memset((void*)&rData, 0x00, sizeof(rData));
	addrlen = sizeof(cliaddr);
	while (readn = recvfrom(sockfd, (char*)&rData, sizeof(rData), 0, (struct sockaddr*)&cliaddr, &addrlen)) {
		addrlen = sizeof(sock_addr);
		getpeername(sockfd, (struct sockaddr*) &sock_addr, &addrlen);
		
		//printf("Read Data %d %s(%d) : %s", GetCurrentThreadId(),
		//	inet_ntoa(sock_addr.sin_addr),
		//	ntohs(sock_addr.sin_port),
		//	szReceiveBuffer
		//);
		cDir = rData.dir;
		doFlip = rData.doFlip;

		switch (cDir) {
		case UP:
			Player1.goUp();
			break;
		case DOWN:
			Player1.goDown();
			break;
		case LEFT:
			Player1.goLeft();
			break;
		case RIGHT:
			Player1.goRight();
			break;
		}
		if (doFlip) {
			int x = Player1.getX();
			int y = Player1.getY();
			game.rcTileOpenner(x, y);
			doFlip = false;
		}
		writen = send(sockfd, szReceiveBuffer, readn, 0);

		memset((void*)&sMapData, 0x00, sizeof(sMapData));
		for (int y = 0; y < MAPSIZEY; y++) {
			for (int x = 0; x < MAPSIZEX; x++) {
				sMapData.map[y][x] = htonl(game.getMapNum(y, x));
			}
		}
		//Ŭ���̾�Ʈ �ּ��� ũ��

		//Ŭ���̾�Ʈ�� ���� rdata(cal_data ����ü)�� ���� ����
		
		addrlen = sizeof(cliaddr);
		sendto(sockfd, (char*)&sMapData, sizeof(sMapData), 0, (struct sockaddr*)&cliaddr, addrlen);
	}

	closesocket(sockfd);
	printf("Thread Close : %d\n", GetCurrentThreadId());

	return 0;

}

int getNum(const int MAX)
{
	int Num = 0;
	bool isFail = true;

	do {
		cout << "10 �̻� " << MAX <<  " ���� �Է� : ";
		cin >> Num;

		if (cin.fail()) {
			cout << "Ʋ�� ���Դϴ�. �ٽ� �Է��Ͽ� �ּ���." << endl;
			cin.clear();
			rewind(stdin);
			isFail = true;
		}
		else if (Num > MAX || Num < 10) {
			cout << MAX << " ����, 10 �̻��� ���� �Է��� �ּ���." << endl;
			cin.clear();
			rewind(stdin);
			isFail = true;
		}
		else if (!cin.fail()) {
			isFail = false;
		}

	} while (isFail == true);

	return Num;
}