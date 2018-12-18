#pragma comment(lib, "ws2_32")	// 윈도우 소켓 라이브러리
#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <stdio.h>		//표준 입출력 헤더
#include <WinSock2.h>	//윈도우서 TCP/IP 통신 프로그램을 구축하기 위한 헤더
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

void ErrorHandling(char * message);	//에러에 대한 문자열을 출력하기 위한 함수

unsigned WINAPI Client1_Thread(void *data);
unsigned WINAPI Client2_Thread(void *data);
unsigned WINAPI Client3_Thread(void *data);
unsigned WINAPI Client4_Thread(void *data);

#define MAX_PACKETLEN 256
#define MAX_CLIENTNUM 1		//접속할 클라이언트 수 1~4 사이

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
struct sockaddr_in servAddr, clntAddr;	//IPv4 주소정보 구조체
SOCKET hServSock, hClntSock[4];	//소켓 생성
int clntAdrSize;	//주소의 길이를 저장할 정수 변수
struct key_data rData[MAX_CLIENTNUM];	//클라이언트와 주고 받을 정보를 저장할 구조체
struct StCData sMapData;

HANDLE h_Mutex;
HANDLE h_Thread[MAX_CLIENTNUM];


int main(int argc, char ** argv) {
	ScreenInit();	// 화면 초기화
	//프로그램의 타이틀 이름 설정
	system("title MineSweepers_server_win port(7777)");

	//HANDLE hThread;
	WSADATA wsaData;

	//윈속 버전 2,2
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error!");	//오류 문구 출력 및 프로그램 종료(윈속초기화)
	}
	//TCP;
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET) {
		ErrorHandling("socket() error");	//오류 문구 출력 및 프로그램 종료(소켓 에러)
	}

	//주소 구조체 초기화
	ZeroMemory(&servAddr, sizeof(struct sockaddr_in));

	//서버의 주소 정보
	servAddr.sin_family = AF_INET;	//IPv4 프로토콜
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	//모든 주소에서의 접속을 받아들임
	servAddr.sin_port = htons(PORT_NUM);	//포트 주소 (PORT_NUM의 값 (7777))

	//bind
	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		ErrorHandling("bind() error");
	}

	if (SOCKET_ERROR == listen(hServSock, 5) == SOCKET_ERROR) {
		return 0;
	}

	ZeroMemory(&clntAddr, sizeof(struct sockaddr_in));

	h_Mutex = CreateMutex(NULL, FALSE, NULL);

	//게임 맵 초기화
	srand((unsigned int)time(NULL));
	game.rstMap(MAPSIZEX, MAPSIZEY, MINES);


	//클라이언트 스레드
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


	//게임 로직
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
		ScreenClear();	// 화면 지우기
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
				ScreenPrint(0, MAPSIZEY + 5, "< 성공 >\n지뢰를 제외한 모든 타일을 열었습니다!\n");
				break;
			case 2:
				ScreenPrint(0, MAPSIZEY + 5, "< 실패 >\n지뢰가 폭발하였습니다.\n");
				break;
			}
		}
		ScreenPrint(0, MAPSIZEY + 1, "방향키로 커서 이동, 'Space'키로 타일 확인");
		ScreenFlipping();	// 버퍼 플립


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