#pragma comment(lib, "ws2_32")	// 윈도우 소켓 라이브러리
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>		//표준 입출력 헤더
#include <stdlib.h>		//문자열 변환을 위한 표준 라이브러리 헤더
#include <string.h>		//문자열을 다루기 위한 라이브러리 헤더
#include <WinSock2.h>	//윈도우서 TCP/IP 통신 프로그램을 구축하기 위한 헤더

#define BUF_SIZE 1024	//BUF_SIZE 를 상수 (int)1024로 선언

//메인 아래 구현한 함수들을 사용하기 위한 선언
void ErrorHandling(char *message);	//에러에 대한 문자열을 출력하기 위한 함수

//메인의 명령 인수로는 IPv4(127.0.0.1)와 포트(9190)가 들어간다
int main(int argc, char * argv[]) {

	//프로그램의 타이틀 이름 설정
	system("title echo_client_win 127.0.0.1 9190");

	WSADATA wsaData;	//윈속 초기화
	SOCKET hSocket;		//소켓 생성
	char message[BUF_SIZE];	//메시지 배열
	int strLen;	//정수 변수 초기화
	SOCKADDR_IN servAdr;	//IPv4 주소정보 구조체

	// 만약 main함수에 전달된 인자의 수가 3가 아닐 경우
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);	//정보를 표시함
		exit(1);	//프로그램 종료
	}

	//만약 윈속 버전 2.2의 초기화값이 성공이 아닐 경우
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error!");	//오류 문구 출력 및 프로그램 종료(윈속초기화)
	}

	//IPv4 프로토콜, TCP 방식의 소켓
	hSocket = socket(PF_INET, SOCK_STREAM, 0);

	//만약 소켓 생성에 실패할 경우
	if (hSocket == INVALID_SOCKET) {
		ErrorHandling("socket() error");	//오류 문구 출력 및 프로그램 종료(소켓 에러)
	}

	//주소를 0으로 주소의 길이만큼 설정
	memset(&servAdr, 0, sizeof(servAdr));

	//주소 정보
	servAdr.sin_family = AF_INET;	//주소는 IPv4 프로토콜
	servAdr.sin_addr.s_addr = inet_addr(argv[1]);	//자신의 IP주소를 할당(main함수 명령인수)
	servAdr.sin_port = htons(atoi(argv[2]));	//자신의 프로그램 포트를 할당(main함수 명령인수)

	//서버와의 접속에 실패할 경우
	if (connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR) {
		ErrorHandling("connect() error!");	//오류 문구 출력 및 프로그램 종료(connect 에러)
	}
	//아니면
	else {
		puts("Connected........."); //연결되었다 표시
	}
	//루프
	while (true) {
		//문자열을 입력받는다.
		fputs("input message(Q to quit): ", stdout);
		//입력받은 문자열을 message변수에 대입한다
		fgets(message, BUF_SIZE, stdin);

		//만약 q 나 Q를 단독으로 입력하고 엔터를 눌렀을 경우 루프를 탈출한다
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
			break;
		}
		
		//서버에 입력받은 메시지를 송신한다.
		send(hSocket, message, strlen(message), 0);
		//서버에서 송신한 메시지를 수신하고, 그 바이트 수를 strLen에 대입한다
		strLen = recv(hSocket, message, BUF_SIZE - 1, 0);
		message[strLen] = 0;	//문자열의 마지막에 0을 대입
		printf("Message from server: %s", message);	//수신받은 메시지를 출력한다.
	}

	closesocket(hSocket);	//소켓을 닫는다
	WSACleanup();	//윈속 해제
	return 0;	//main 함수 반환
}

//에러문구 출력 및 프로그램 종료를 위한 함수
void ErrorHandling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}