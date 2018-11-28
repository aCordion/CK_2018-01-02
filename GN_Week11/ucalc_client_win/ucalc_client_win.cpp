//201813113 김일수

#pragma comment(lib, "ws2_32")	// 윈도우 소켓 라이브러리
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>		//표준 입출력 헤더
#include <WinSock2.h>	//윈도우서 TCP/IP 통신 프로그램을 구축하기 위한 헤더

#define PORT_NUM 3800	// 정수 3800 를 상수 PORT_NUM로 선언
#define MAXLEN 256	// 정수 256 를 상수 MAXLEN로 선언

struct cal_data {	//cal_data 구조체 선언
	int left_num;	//왼쪽 피연산자
	int right_num;	//오른쪽 피연산자
	char op;		//연산자
	int result;		//결과값
	short int error;	//에러
};

//main의 명령 인수로 127.0.0.1 이 들어감
int main(int argc, char ** argv) {

	//프로그램의 타이틀 이름 설정
	system("title ucalc_client_win 127.0.0.1");

	SOCKET sockfd;	//소켓 생성
	WSADATA wsaData;	//윈속 초기화
	struct sockaddr_in addr, recvaddr;	//IPv4 주소정보 구조체
	struct cal_data sdata;	//서버와 주고 받을 정보를 저장할 구조체

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
	addr.sin_port = htons(PORT_NUM);	//자신의 프로그램 포트를 할당(상수 PORT_NUM(3800))

	//반복
	while (true) {
		printf("> ");	//입력할 수 있다는 간접적인 표현으로 특수기호를 출력
		//msg 변수에 사용자의 입력 값을 저장
		fgets(msg, MAXLEN - 1, stdin);
		//만약 입력 값이 quit이면
		if (strncmp(msg, "quit\n", 5) == 0) {
			break;	//반복문 탈출
		}
		//msg 변수에 저장된 문자 중 처음 숫자들을 left_num에, 숫자가 아닌 것은 op에, 그 다음으로 나오는 숫자들은 right_num에 저장
		sscanf(msg, "%d%[^0-9]%d", &left_num, op, &right_num);

		//sdata의 값들을 0으로 초기화
		memset((void*)&sdata, 0x00, sizeof(sdata));

		//sdata.left_num의 값에 호스트 바이트 정렬 방식의 left_num 값을 4바이트 네트워크 바이트 정렬 방식으로 변환 후 저장
		sdata.left_num = htonl(left_num);
		//sdata.right_num의 값에 호스트 바이트 정렬 방식의 right_num 값을 4바이트 네트워크 바이트 정렬 방식으로 변환 후 저장
		sdata.right_num = htonl(right_num);
		//sdata.op의 값에 op[0]의 값 대입
		sdata.op = op[0];

		int tmp;	//임시 정수 변수를 선언
		//addrlen에 addr값의 길이를 저장
		addrlen = sizeof(addr);
		//tmp에 서버로의 송신이 성공적으로 이루어졌는지에 대한 결과값을 대입(디버그)
		tmp = sendto(sockfd, (char *)&sdata, sizeof(sdata), 0, (struct sockaddr*)&addr, addrlen);
		//addrlen에 recvaddr값의 길이를 저장
		addrlen = sizeof(recvaddr);
		//tmp에 서버로 부터의 수신이 성공적으로 이루어졌는지에 대한 결과값을 대입(디버그)
		tmp = recvfrom(sockfd, (char *)&sdata, sizeof(sdata), 0, (struct sockaddr*)&recvaddr, &addrlen);
		//서버로 부터 수신한 값을 출력해준다.
		printf("%d %c %d = %d\n", ntohl(sdata.left_num), sdata.op, ntohl(sdata.right_num), ntohl(sdata.result));
	}
	closesocket(sockfd);	//소켓을 닫음
	WSACleanup();	//윈속 초기화
	return 0;	//main함수를 반환
}