//201813113 김일수

#pragma comment(lib, "ws2_32")	// 윈도우 소켓 라이브러리
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>		//표준 입출력 헤더
#include <WinSock2.h>	//윈도우서 TCP/IP 통신 프로그램을 구축하기 위한 헤더

#define DEBUG			// DEBUG Build
#define PORT_NUM 3800	// 정수 3800 를 상수 PORT_NUM로 선언

struct cal_data {	//cal_data 구조체 선언
	int left_num;	//왼쪽 피연산자
	int right_num;	//오른쪽 피연산자
	char op;		//연산자
	int result;		//결과값
	short int error;	//에러
};

int main(int argc, char ** argv) {

	//프로그램의 타이틀 이름 설정
	system("title ucalc_server_win");

	SOCKET sockfd;	//소켓 생성
	int addrlen;	//주소의 길이를 저장할 정수 변수
	int cal_result;	//연산 결과값을 저장할 정수 변수
	int left_num, right_num;	//왼쪽, 오른쪽 피연산자를 저장할 정수 변수
	struct sockaddr_in addr, cliaddr;	//IPv4 주소정보 구조체
	struct cal_data rdata;	//클라이언트와 주고 받을 정보를 저장할 구조체

	WSADATA wsaData;	//윈속 초기화

	//만약 윈속 버전 2.2의 초기화값이 성공이 아닐 경우
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
		return 1;	//main함수 반환
	}

	//만약 서버 소켓 생성에 실패할 경우
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		return 1;	//main함수 반환
	}
	//서버 주소를 0으로 서버 주소의 길이만큼 설정
	memset((void*)&addr, 0x00, sizeof(addr));

	//서버의 주소 정보
	addr.sin_family = AF_INET;	//서버 주소는 IPv4 프로토콜
	addr.sin_addr.s_addr = htonl(INADDR_ANY);	//모든 주소에서의 접속을 받아들임
	addr.sin_port = htons(PORT_NUM);	//포트 주소 (상수 PORT_NUM의 값 (3800))

	//주소의 크기
	addrlen = sizeof(addr);

	//서버 소켓을 소프트웨어 포트와 IP로 묶는 데에 실패할 경우
	if (bind(sockfd, (struct sockaddr *)&addr, addrlen) == -1) {
		return 1;	//main함수 반환
	}

	//반복
	while (true) {
		//클라이언트 주소의 크기
		addrlen = sizeof(cliaddr);
		//클라이언트로 부터 rdata(cal_data 구조채)의 값을 수신
		recvfrom(sockfd, (char*)&rdata, sizeof(rdata), 0, (struct sockaddr*)&cliaddr, &addrlen);

#ifdef DEBUG	//만약 이 빌드가 DEBUG로 선언된 상태라면
		//클라이언트의 주소와 포트 정보를 서버에 출력, 줄바꿈
		printf("info : %s (%d)\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
		//클라이언트에게 받은 왼쪽 피연산자, 연산자, 오른쪽 피연산자를 출력, 줄바꿈
		printf("%d %c %d\n", ntohl(rdata.left_num),rdata.op, ntohl(rdata.right_num));
#endif	// ifdef DEBUG의 끝
		//네트워크 바이트 정렬 방식의 4바이트 데이터인 rdata.left_num값을 호스트 바이트 정렬 방식으로 left_num변수에 저장
		left_num = ntohl(rdata.left_num);
		//네트워크 바이트 정렬 방식의 4바이트 데이터인 rdata.right_num값을 호스트 바이트 정렬 방식으로 right_num변수에 저장
		right_num = ntohl(rdata.right_num);

		//rdata.op값에 따른 switch 제어문
		switch (rdata.op) {
		case '+':	//만약 rdata.op가 char형의 '+'이면
			//cal_result값에 left_num과 right_num을 더한 값을 대입
			cal_result = left_num + right_num;
			break;	//switch 제어문 탈출
		case '-':	//만약 rdata.op가 char형의 '-'이면
			//cal_result값에 left_num과 right_num을 뺀 값을 대입
			cal_result = left_num - right_num;
			break;	//switch 제어문 탈출
		case '*':	//만약 rdata.op가 char형의 '*'이면
			//cal_result값에 left_num과 right_num을 곱한 값을 대입
			cal_result = left_num * right_num;
			break;	//switch 제어문 탈출
		case '/':	//만약 rdata.op가 char형의 '/'이면
			//만약 right_num이 0이라면
			if (right_num == 0) {
				//rdata.error에 호스트 바이트 정렬 방식의 2바이트 데이터인 2를 네트워크 바이트 정렬 방식으로 저장
				rdata.error = htons(2);
				break;	//switch 제어문 탈출
			}
			//cal_result값에 left_num과 right_num을 나눈 값을 대입
			cal_result = left_num / right_num;
			break;	//switch 제어문 탈출
		}
		//rdata.result에 호스트 바이트 정렬 방식의 4바이트 데이터인 car_result를 네트워크 바이트 정렬 방식으로 저장
		rdata.result = htonl(cal_result);
		//클라이언트에게 계산을 끝낸 rdara 구조체를 전송
		sendto(sockfd, (char*)&rdata, sizeof(rdata), 0, (struct sockaddr*)&cliaddr, addrlen);
	}
	closesocket(sockfd);	//소켓을 닫음
	WSACleanup();	//윈속 초기화
	return 0;	//main함수 반환
}