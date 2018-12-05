#pragma comment(lib, "ws2_32")	// 윈도우 소켓 라이브러리
#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <stdio.h>		//표준 입출력 헤더
#include <WinSock2.h>	//윈도우서 TCP/IP 통신 프로그램을 구축하기 위한 헤더

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
void ErrorHandling(char * message);	//에러에 대한 문자열을 출력하기 위한 함수
DWORD WINAPI t_func(void *data);

CGameMap game(MAPSIZEX, MAPSIZEY, MINES);
CMyCursor Player1(1, 1, MAPSIZEX, MAPSIZEY, false);
CMyCursor Player2(38, 1, MAPSIZEX, MAPSIZEY, false);
CMyCursor Player3(1, 18, MAPSIZEX, MAPSIZEY, false);
CMyCursor Player4(38, 18, MAPSIZEX, MAPSIZEY, false);


char cDir;
bool doFlip;
struct sockaddr_in servAddr, clntAddr;	//IPv4 주소정보 구조체
struct key_data rData;	//클라이언트와 주고 받을 정보를 저장할 구조체
struct StCData sMapData;

int main(int argc, char ** argv) {
	ScreenInit();	// 화면 초기화
	//프로그램의 타이틀 이름 설정
	system("title MineSweepers_server_win port(7777)");

	SOCKET hServSock, hClntSock;	//소켓 생성
	HANDLE hThread;
	int clntAdrSize;	//주소의 길이를 저장할 정수 변수

	WSADATA wsaData;	//윈속 초기화

	//만약 윈속 버전 2.2의 초기화값이 성공이 아닐 경우
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error!");	//오류 문구 출력 및 프로그램 종료(윈속초기화)
	}

	hServSock = socket(PF_INET, SOCK_STREAM, 0);	//서버 소켓은 IPv4 프로토콜, TCP 방식의 소켓
	if (hServSock == INVALID_SOCKET) {
		ErrorHandling("socket() error");	//오류 문구 출력 및 프로그램 종료(소켓 에러)
	}

	//서버 주소를 0으로 서버 주소의 길이만큼 설정
	//memset((void*)&servAddr, 0x00, sizeof(servAddr));
	ZeroMemory(&servAddr, sizeof(struct sockaddr_in));

	//서버의 주소 정보
	servAddr.sin_family = AF_INET;	//서버 주소는 IPv4 프로토콜
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	//모든 주소에서의 접속을 받아들임
	servAddr.sin_port = htons(PORT_NUM);	//포트 주소 (상수 PORT_NUM의 값 (7777))

	//서버 소켓을 소프트웨어 포트와 IP로 묶는 데에 실패할 경우
	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		ErrorHandling("bind() error");	//오류 문구 출력 및 프로그램 종료(bind 에러)
	}

	if (SOCKET_ERROR == listen(hServSock, 5) == SOCKET_ERROR) {
		return 0;
	}

	ZeroMemory(&clntAddr, sizeof(struct sockaddr_in));

	srand((unsigned int)time(NULL));
	

	clock_t oldTime, curTime;
	oldTime = clock();

	while (true) {
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
		//ScreenPrint(0, MAPSIZEY + 2, "'R'키를 눌러 다시 시작 합니다.\n'ESC'키를 눌러 종료합니다.");
		ScreenFlipping();	// 화면에 보여주기


	}
	{
	//game.rstMap(MAPSIZEX, MAPSIZEY, MINES);

	//// game logic
	//while (true) {

	//	// draw call
	//	ScreenClear();	// 화면 지우기
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
	//			ScreenPrint(0, MAPSIZEY + 5, "< 성공 >\n지뢰를 제외한 모든 타일을 열었습니다!\n");
	//			break;
	//		case 2:
	//			ScreenPrint(0, MAPSIZEY + 5, "< 실패 >\n지뢰가 폭발하였습니다.\n");
	//			break;
	//		}
	//	}
	//	ScreenPrint(0, MAPSIZEY + 1, "방향키로 커서 이동, 'Space'키로 타일 확인");
	//	//ScreenPrint(0, MAPSIZEY + 2, "'R'키를 눌러 다시 시작 합니다.\n'ESC'키를 눌러 종료합니다.");
	//	ScreenFlipping();	// 화면에 보여주기

	//	memset((void*)&sMapData, 0x00, sizeof(sMapData));
	//	for (int y = 0; y < MAPSIZEY; y++) {
	//		for (int x = 0; x < MAPSIZEX; x++) {
	//			sMapData.map[y][x] = htonl(game.getMapNum(y, x));
	//		}
	//	}
	//	//클라이언트 주소의 크기
	//	addrlen = sizeof(cliaddr);
	//	//클라이언트로 부터 rdata(cal_data 구조체)의 값을 수신
	//	recvfrom(sockfd, (char*)&rData, sizeof(rData), 0, (struct sockaddr*)&cliaddr, &addrlen);
	//	addrlen = sizeof(cliaddr);
	//	sendto(sockfd, (char*)&sMapData, sizeof(sMapData), 0, (struct sockaddr*)&cliaddr, addrlen);

	//	
	//	// 키보드 입력 처리
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
	closesocket(hServSock);	//소켓을 닫음
	WSACleanup();	//윈속 초기화
	ScreenRelease();	//화면 해제

	return 0;
}

#define MAX_PACKETLEN 256
#define MAX_CLIENTNUM 4
int clientIdData[4];
int clientIdcurPos = 0;
bool clientIdAlready = false;

DWORD WINAPI t_func(void *data) {

	SOCKET sockfd = (SOCKET)data;
	int readn, writen;
	int addrlen;
	struct sockaddr_in sock_addr;
	char szReceiveBuffer[MAX_PACKETLEN];

	printf("Thread Start : %d\n", GetCurrentThreadId());
	memset((void*)&rData, 0x00, sizeof(rData));
	addrlen = sizeof(sock_addr);
	while (readn = recv(sockfd, (char*)&rData, sizeof(rData)-1, 0)) {
		addrlen = sizeof(sock_addr);
		getpeername(sockfd, (struct sockaddr*) &sock_addr, &addrlen);
		
		for (int i = 0; i < MAX_CLIENTNUM; i++) {
			if (clientIdData[i] == GetCurrentThreadId()) {
				clientIdAlready = true;
			}
		}
		if (!clientIdAlready && (clientIdcurPos <= 4)) {
			clientIdData[clientIdcurPos++] = GetCurrentThreadId();
		}

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
		//클라이언트 주소의 크기

		//클라이언트로 부터 rdata(cal_data 구조체)의 값을 수신
		
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
		cout << "10 이상 " << MAX <<  " 이하 입력 : ";
		cin >> Num;

		if (cin.fail()) {
			cout << "틀린 값입니다. 다시 입력하여 주세요." << endl;
			cin.clear();
			rewind(stdin);
			isFail = true;
		}
		else if (Num > MAX || Num < 10) {
			cout << MAX << " 이하, 10 이상의 값을 입력해 주세요." << endl;
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

void ErrorHandling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}