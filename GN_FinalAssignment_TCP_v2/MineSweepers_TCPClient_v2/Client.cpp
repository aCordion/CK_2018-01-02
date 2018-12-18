//201813113 김일수
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
	//char dir;		//방향
	int x, y;		//좌표
	bool doFlip;	//플립
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
char *imgs[] = { "○","①","②","③","④","⑤","⑥","⑦","⑧","☆","□" };

unsigned WINAPI getCursor(void *data);
void cursorCon();
HANDLE h_getCursor;
CGameMap map(MAPSIZEX,MAPSIZEY,0);
CMyCursor Cursor(1, 1, 40, 20, true);
CMyCursor Cursor1(1, 1, 40, 20, true);
CMyCursor Cursor2(1, 1, 40, 20, true);
CMyCursor Cursor3(1, 1, 40, 20, true);
CMyCursor Cursor4(1, 1, 40, 20, true);

SOCKET sockfd;	//소켓 생성
int otherX[4];
int otherY[4];
struct key_data sData;
struct key_data rData;
struct pos_data rpData;

int main(int argc, char ** argv) {
	ScreenInit();	// 화면 초기화
	//프로그램의 타이틀 이름 설정
	system("title MineSweepers_client_win 127.0.0.1");

	
	WSADATA wsaData;	//윈속 초기화
	struct sockaddr_in servAdr;	//IPv4 주소정보 구조체
										
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

	//맵 동기화
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
	//메인 로직
	while (true) {
		ScreenClear();	// 화면 지우기
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
				ScreenPrint(otherX[i] * 2, otherY[i], "◈");
			}*/
		}
		else {
			map.allTileOpen();
			switch (map.getCheckStatus()) {
			case 1:
				ScreenPrint(0, MAPSIZEY + 5, "< 성공 >\n지뢰를 제외한 모든 타일을 열었습니다!\n");
				break;
			case 2:
				ScreenPrint(0, MAPSIZEY + 5, "< 실패 >\n지뢰가 폭발하였습니다.\n");
				break;
			}
		}

		ScreenPrint(0, MAPSIZEY + 1, "방향키로 커서 이동, 'Space'키로 타일 확인");
		ScreenFlipping();	// 버퍼 출력
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
		//ScreenFlipping();	// 버퍼 출력
	}
	return 0;
}
