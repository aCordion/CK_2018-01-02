#pragma comment(lib, "ws2_32")	// 윈도우 소켓 라이브러리
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>		//표준 입출력 헤더
#include <stdlib.h>		//문자열 변환을 위한 표준 라이브러리 헤더
#include <string.h>		//문자열을 다루기 위한 라이브러리 헤더
#include <WinSock2.h>	//윈도우서 TCP/IP 통신 프로그램을 구축하기 위한 헤더

#define BUF_SIZE 1024	//BUF_SIZE 를 상수 (int)1024로 선언

//메인 아래 구현한 함수들을 사용하기 위한 선언
void ErrorHandling(char *message);	//에러에 대한 문자열을 출력하기 위한 함수

//메인의 명령 인수로는 포트(9190)가 들어간다
int main(int argc, char *argv[]) {

	//프로그램의 타이틀 이름 설정
	system("title echo_server_win 9190");

	WSADATA wsaData;	//윈속 초기화
	SOCKET hServSock, hClntSock;	//소켓 생성	
	char message[BUF_SIZE];	//메시지 배열
	int strLen, i;	//정수 변수 초기화

	SOCKADDR_IN servAdr, clntAdr;	//IPv4 주소정보 구조체
	int clntAdrSize; // 클라이언트 주소 크기를 위한 변수

	//만약 main함수에 전달된 인자의 수가 2가 아닐 경우
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);	//정보를 표시함
		exit(1);	//프로그램 종료
	}

	//만약 윈속 버전 2.2의 초기화값이 성공이 아닐 경우
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error!");	//오류 문구 출력 및 프로그램 종료(윈속초기화)
	}
	hServSock = socket(PF_INET, SOCK_STREAM, 0);	//서버 소켓은 IPv4 프로토콜, TCP 방식의 소켓
	
	//만약 서버 소켓 생성에 실패할 경우
	if (hServSock == INVALID_SOCKET) {
		ErrorHandling("socket() error");	//오류 문구 출력 및 프로그램 종료(소켓 에러)
	}
	//서버 주소를 0으로 서버 주소의 길이만큼 설정
	memset(&servAdr, 0, sizeof(servAdr));
	//서버의 주소 정보
	servAdr.sin_family = AF_INET;	//서버 주소는 IPv4 프로토콜
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);	//모든 주소에서의 접속을 받아들임
	servAdr.sin_port = htons(atoi(argv[1]));	//포트 주소 (main함수의 명령인수)

	//서버 소켓을 소프트웨어 포트와 IP로 묶는 데에 실패할 경우
	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR) {
		ErrorHandling("bind() error");	//오류 문구 출력 및 프로그램 종료(bind 에러)
	}

	//클라이언트의 접속 요청을 위한 서버의 대기모드 설정이 실패할 경우
	if (listen(hServSock, 5) == SOCKET_ERROR) {
		ErrorHandling("listen() error");	//오류 문구 출력 및 프로그램 종료 (listen 에러)
	}

	//클라이언트 주소 크기
	clntAdrSize = sizeof(clntAdr);

	for (i = 0; i < 5; i++) {	//5회 루프
		//클라이언트 소켓의 접속을 허용
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSize);

		//만약 클라리언트 소켓의 접속의 허용에 실패하였을 경우
		if (hClntSock == -1) {
			ErrorHandling("accept() error");	//오류 문구 출력 및 프로그램 종료(accept 에러)
		}
		else {	//아니면
			printf("Connected client %d \n", i + 1);	//몇번째 클라이언트가 접속했는지 출력
		}
		//수신한 메시지의 바이트 수가 0이 아닐 경우 루프
		while ((strLen = recv(hClntSock, message, BUF_SIZE, 0)) != 0) {
			//수신받은 문자열을 클라이언트에게 송신
			send(hClntSock, message, strLen, 0);
		}
		closesocket(hClntSock);	//클라이언트 소켓을 닫음
	}
	closesocket(hServSock);	//서버 소켓을 닫음
	WSACleanup();	//윈속 해제
	return 0;	//main함수 반환
}

//에러문구 출력 및 프로그램 종료를 위한 함수
void ErrorHandling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}