//201813113 김일수
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
	//char dir;		//방향
	int x, y;		//좌표
	bool doFlip;	//플립
};
struct StCData {
	int map[MAPSIZEY][MAPSIZEX];
	//char map[MAPSIZEY][MAPSIZEX];
};
//   *imgs[] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10  };
char *imgs[] = { "○","①","②","③","④","⑤","⑥","⑦","⑧","☆","□" };


int main(int argc, char ** argv) {
	ScreenInit();	// 화면 초기화
	//프로그램의 타이틀 이름 설정
	system("title MineSweepers_client_win 127.0.0.1");

	SOCKET sockfd;	//소켓 생성
	WSADATA wsaData;	//윈속 초기화
	struct sockaddr_in servAdr;	//IPv4 주소정보 구조체
										
	CMyCursor Cursor(1, 1 ,40 ,20 ,false);

	struct key_data sData;
	struct StCData rMapData;

	//if (argc != 2) {
	//	printf("Usage : %s [ip address]\n", argv[0]);
	//	return 1;	//main함수 반환
	//}

	// 만약 윈속 초기화에 실패하는 경우
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
		return 1;	//main함수 반환
	}

	//IPv4 프로토콜, TCP 방식의 소켓
	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	//소켓 생성 실패
	if (sockfd == INVALID_SOCKET) {
		return -1;
	}

	//주소 구조체 초기화
	memset((void*)&servAdr, 0x00, sizeof(servAdr));

	//주소 정보
	servAdr.sin_family = AF_INET;	//IPv4 프로토콜
	//servAdr.sin_addr.s_addr = inet_addr(argv[1]);	//자신의 IP주소를 할당(main함수 명령인수)
	servAdr.sin_addr.s_addr = inet_addr(IP_NUM); //IP_NUM("127.0.0.1")
	servAdr.sin_port = htons(PORT_NUM);	//PORT_NUM(7777)

    //connect
	if (connect(sockfd, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR) {
		return -1;
	}
	//메인 로직
	while (true) {
		ScreenClear();	// 화면 지우기

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
			ScreenPrint(0, MAPSIZEY + 1, "방향키로 커서 이동, 'Space'키로 타일 확인");
			ScreenFlipping();	// 버퍼 출력
		}
	}
	closesocket(sockfd);
	WSACleanup();
	ScreenRelease();
	return 0;
}