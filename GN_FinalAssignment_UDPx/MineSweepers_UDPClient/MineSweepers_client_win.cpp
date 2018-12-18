//201813113 김일수
#pragma comment(lib, "ws2_32")	// 윈도우 소켓 라이브러리
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>		//표준 입출력 헤더
#include <WinSock2.h>	//윈도우서 TCP/IP 통신 프로그램을 구축하기 위한 헤더

#include <conio.h>
#include "util.h"

#define PORT_NUM 7777
#define MAXLEN 256	// 정수 256 를 상수 MAXLEN로 선언

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
char *imgs[] = { "○","①","②","③","④","⑤","⑥","⑦","⑧","☆"};

//main의 명령 인수로 127.0.0.1 이 들어감
int main(int argc, char ** argv) {
	ScreenInit();	// 화면 초기화
	//프로그램의 타이틀 이름 설정
	system("title MineSweepers_client_win 127.0.0.1");

	SOCKET sockfd;	//소켓 생성
	WSADATA wsaData;	//윈속 초기화
	struct sockaddr_in addr, recvaddr;	//IPv4 주소정보 구조체
	//struct cal_data sdata;	//서버와 주고 받을 정보를 저장할 구조체
	struct key_data sData;
	struct StCData rMapData;

	char msg[MAXLEN];	//클라이언트에서 사용자가 입력한 정보를 받는 char변수
	int left_num;	//왼쪽 피연산자
	int right_num;	//오른쪽 피연산자
	int addrlen;	//주소길이

	char op[2];	//연산자를 저장할 변수

	// 만약 main함수에 전달된 인자의 수가 2가 아닐 경우
	if (argc != 2) {
		printf("Usage : %s [ip address]\n", argv[0]);
		return 1;	//main함수 반환
	}

	// 만약 윈속 초기화에 실패하는 경우
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
		return 1;	//main함수 반환
	}

	//만약 소켓 생성에 실패할 경우
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		return 1;//main함수 반환
	}

	//주소를 0으로 주소의 길이만큼 설정
	memset((void*)&addr, 0x00, sizeof(addr));

	//주소 정보
	addr.sin_family = AF_INET;	//주소는 IPv4 프로토콜
	addr.sin_addr.s_addr = inet_addr(argv[1]);	//자신의 IP주소를 할당(main함수 명령인수)
	addr.sin_port = htons(PORT_NUM);	//자신의 프로그램 포트를 할당(상수 PORT_NUM(7777))
	
	//반복
	while (true) {
		ScreenClear();	// 화면 지우기

		

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
		ScreenFlipping();	// 화면에 보여주기
		//addrlen = sizeof(recvaddr);
		//recvfrom(sockfd, (char *)&sData, sizeof(sData), 0, (struct sockaddr*)&recvaddr, &addrlen);
		//서버로 부터 수신한 값을 출력해준다.
		//printf("%d %c %d = %d\n", ntohl(sData.left_num), sdata.op, ntohl(sdata.right_num), ntohl(sdata.result));
	}
	closesocket(sockfd);	//소켓을 닫음
	WSACleanup();	//윈속 초기화
	ScreenRelease();
	return 0;	//main함수를 반환
}