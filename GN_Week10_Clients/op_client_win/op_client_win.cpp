#pragma comment(lib, "ws2_32")	// 윈도우 소켓 라이브러리
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>		//표준 입출력 헤더
#include <stdlib.h>		//문자열 변환을 위한 표준 라이브러리 헤더
#include <string.h>		//문자열을 다루기 위한 라이브러리 헤더
#include <WinSock2.h>	//윈도우서 TCP/IP 통신 프로그램을 구축하기 위한 헤더

#define BUF_SIZE 1024	//BUF_SIZE 를 상수 (int)1024로 선언
#define RLT_SIZE 4		//RLT_SIZE 를 상수 (int)4로 선언
#define OPSZ 4			//OPSZ 를 상수 (int)4로 선언

//메인 아래 구현한 함수들을 사용하기 위한 선언
void ErrorHandling(char *message);	//에러에 대한 문자열을 출력하기 위한 함수

//메인의 명령 인수로는 IPv4(127.0.0.2)와 포트(9191)가 들어간다
int main(int argc, char *argv[]) {

	//프로그램의 타이틀 이름 설정
	system("title op_client_win 127.0.0.2 9191");

	WSADATA wsaData;	//윈속 초기화
	SOCKET hSocket;		//소켓 생성
	char opmsg[BUF_SIZE];	//계산할 수 배열
	int result, opndCnt, i;	//정수 변수 초기화
	SOCKADDR_IN servAdr;	//IPv4 주소정보 구조체

	// 만약 main함수에 전달된 인자의 수가 3가 아닐 경우
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	// 만약 윈속 초기화에 실패하는 경우
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error!");//오류 문구 출력 및 프로그램 종료(윈속초기화)
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

	//연산할 값의 갯수 입력 요청 출력
	fputs("Operand count: ", stdout);
	//연산할 값의 갯수 입력
	scanf("%d", &opndCnt);
	//opmsg[0]에 연산할 값의 갯수 정보를 캐릭터 형태로 대입
	opmsg[0] = (char)opndCnt;

	//연산할 값의 갯수만큼 루프
	for (i = 0; i < opndCnt; i++) {
		//연산할 값 입력 요청 출력
		printf("Operand %d: ", i + 1);
		//연산할 값 입력받으면 opmsg[i*OPSZ+1]에 대입
		scanf("%d", (int*)&opmsg[i*OPSZ + 1]);
	}
	fgetc(stdin);
	//사용할 연산자 입력 요청 출력
	fputs("Operator: ", stdout);
	//사용할 연산자 입력받으면 opmsg[opndCnt*OPSZ+1]에 대입
	scanf("%c", &opmsg[opndCnt*OPSZ + 1]);
	//연산할 내용을 서버로 송신
	send(hSocket, opmsg, opndCnt*OPSZ + 2, 0);
	//서버로부터 수신받은 연산 결과를 result 변수에 대입
	recv(hSocket, (char*)&result, RLT_SIZE, 0);
	
	//서버로부터 수신받은 연산 결과를 출력
	printf("Operation result: %d \n", result);
	closesocket(hSocket); // 소켓을 닫음
	WSACleanup();	//윈속 해제
	return 0;	//main함수 반환
}

//에러문구 출력 및 프로그램 종료를 위한 함수
void ErrorHandling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}