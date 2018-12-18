//201813113 ���ϼ�
#pragma comment(lib, "ws2_32")	// ������ ���� ���̺귯��
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>		//ǥ�� ����� ���
#include <WinSock2.h>	//�����켭 TCP/IP ��� ���α׷��� �����ϱ� ���� ���

#include <conio.h>
#include "util.h"

#define PORT_NUM 7777
#define MAXLEN 256	// ���� 256 �� ��� MAXLEN�� ����

#define MAPSIZEX	40
#define MAPSIZEY	20

struct key_data {
	char dir;
	bool doFlip;
};
struct StCData {
	int map[MAPSIZEY][MAPSIZEX];
	//char map[MAPSIZEY][MAPSIZEX];
};
//   *imgs[] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  };
char *imgs[] = { "��","��","��","��","��","��","��","��","��","��"};

//main�� ��� �μ��� 127.0.0.1 �� ��
int main(int argc, char ** argv) {
	ScreenInit();	// ȭ�� �ʱ�ȭ
	//���α׷��� Ÿ��Ʋ �̸� ����
	system("title MineSweepers_client_win 127.0.0.1");

	SOCKET sockfd;	//���� ����
	WSADATA wsaData;	//���� �ʱ�ȭ
	struct sockaddr_in addr, recvaddr;	//IPv4 �ּ����� ����ü
	//struct cal_data sdata;	//������ �ְ� ���� ������ ������ ����ü
	struct key_data sData;
	struct StCData rMapData;

	char msg[MAXLEN];	//Ŭ���̾�Ʈ���� ����ڰ� �Է��� ������ �޴� char����
	int left_num;	//���� �ǿ�����
	int right_num;	//������ �ǿ�����
	int addrlen;	//�ּұ���

	char op[2];	//�����ڸ� ������ ����

	// ���� main�Լ��� ���޵� ������ ���� 2�� �ƴ� ���
	if (argc != 2) {
		printf("Usage : %s [ip address]\n", argv[0]);
		return 1;	//main�Լ� ��ȯ
	}

	// ���� ���� �ʱ�ȭ�� �����ϴ� ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
		return 1;	//main�Լ� ��ȯ
	}

	//���� ���� ������ ������ ���
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		return 1;//main�Լ� ��ȯ
	}

	//�ּҸ� 0���� �ּ��� ���̸�ŭ ����
	memset((void*)&addr, 0x00, sizeof(addr));

	//�ּ� ����
	addr.sin_family = AF_INET;	//�ּҴ� IPv4 ��������
	addr.sin_addr.s_addr = inet_addr(argv[1]);	//�ڽ��� IP�ּҸ� �Ҵ�(main�Լ� ����μ�)
	addr.sin_port = htons(PORT_NUM);	//�ڽ��� ���α׷� ��Ʈ�� �Ҵ�(��� PORT_NUM(7777))
	
	//�ݺ�
	while (true) {
		ScreenClear();	// ȭ�� �����

		

		memset((void*)&sData, 0x00, sizeof(sData));

		if (_kbhit()) {
			int inKey = _getch();
			switch (inKey) {
			case UP:	
			case DOWN:	
			case LEFT:	
			case RIGHT:	
				sData.dir = (char)inKey;
				break;
			case SPACE:
				sData.doFlip = (char)inKey;
				break;
			}
			addrlen = sizeof(addr);
			sendto(sockfd, (char *)&sData, sizeof(sData), 0, (struct sockaddr*)&addr, addrlen);
		}

		memset((void*)&rMapData, 0x00, sizeof(rMapData));
		addrlen = sizeof(recvaddr);
		recvfrom(sockfd, (char*)&rMapData, sizeof(rMapData), MSG_OOB, (struct sockaddr*)&recvaddr, &addrlen);
		char* temp[MAPSIZEY][MAPSIZEX];

		for (int y = 0; y < MAPSIZEY; y++) {
			for (int x = 0; x < MAPSIZEX; x++) {
				ScreenPrint(x * 2, y, imgs[htonl(rMapData.map[y][x])]);
				//temp[y][x] = &rMapData.map[y][x];
				//ScreenPrint(x * 2, y, temp[y][x]);
			}
		}
		ScreenFlipping();	// ȭ�鿡 �����ֱ�
		//addrlen = sizeof(recvaddr);
		//recvfrom(sockfd, (char *)&sData, sizeof(sData), 0, (struct sockaddr*)&recvaddr, &addrlen);
		//������ ���� ������ ���� ������ش�.
		//printf("%d %c %d = %d\n", ntohl(sData.left_num), sdata.op, ntohl(sdata.right_num), ntohl(sdata.result));
	}
	closesocket(sockfd);	//������ ����
	WSACleanup();	//���� �ʱ�ȭ
	ScreenRelease();
	return 0;	//main�Լ��� ��ȯ
}