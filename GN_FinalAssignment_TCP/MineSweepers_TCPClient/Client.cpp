//201813113 ���ϼ�
#pragma comment(lib, "ws2_32")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>

#include <conio.h>
#include "util.h"
#include "GameMap.h"
#include "MyCursor.h"

#define IP_NUM "127.0.0.1"	//IP
#define PORT_NUM 7777		//port

#define MAPSIZEX	40
#define MAPSIZEY	20


struct key_data {
	//char dir;		//����
	int x, y;		//��ǥ
	bool doFlip;	//�ø�
};
struct StCData {
	int map[MAPSIZEY][MAPSIZEX];
	//char map[MAPSIZEY][MAPSIZEX];
};
//   *imgs[] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10  };
char *imgs[] = { "��","��","��","��","��","��","��","��","��","��","��" };


int main(int argc, char ** argv) {
	ScreenInit();	// ȭ�� �ʱ�ȭ
	//���α׷��� Ÿ��Ʋ �̸� ����
	system("title MineSweepers_client_win 127.0.0.1");

	SOCKET sockfd;	//���� ����
	WSADATA wsaData;	//���� �ʱ�ȭ
	struct sockaddr_in servAdr;	//IPv4 �ּ����� ����ü
										
	CMyCursor Cursor(1, 1 ,40 ,20 ,false);

	struct key_data sData;
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
	//���� ����
	while (true) {
		ScreenClear();	// ȭ�� �����

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
				sData.doFlip = (char)inKey;
				break;
			}
			sData.x = htonl(Cursor.getX());
			sData.y = htonl(Cursor.getY());

			int dataLen = sizeof(sData);
			send(sockfd, (char*)&sData, dataLen, 0);

			memset((void*)&rMapData, 0x00, sizeof(StCData));

			int recvLen;
			recvLen = recv(sockfd, (char*)&rMapData, sizeof(rMapData), 0);

			char* temp[MAPSIZEY][MAPSIZEX];

			for (int y = 0; y < MAPSIZEY; y++) {
				for (int x = 0; x < MAPSIZEX; x++) {
					temp[y][x] = imgs[htonl(rMapData.map[y][x])];
				}
			}
			for (int y = 0; y < MAPSIZEY; y++) {
				for (int x = 0; x < MAPSIZEX; x++) {
					ScreenPrint(x * 2, y, temp[y][x]);
				}
			}
			Cursor.draw();
			ScreenPrint(0, MAPSIZEY + 1, "����Ű�� Ŀ�� �̵�, 'Space'Ű�� Ÿ�� Ȯ��");
			ScreenFlipping();	// ���� ���
		}
	}
	closesocket(sockfd);
	WSACleanup();
	ScreenRelease();
	return 0;
}