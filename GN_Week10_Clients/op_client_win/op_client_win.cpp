#pragma comment(lib, "ws2_32")	// ������ ���� ���̺귯��
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>		//ǥ�� ����� ���
#include <stdlib.h>		//���ڿ� ��ȯ�� ���� ǥ�� ���̺귯�� ���
#include <string.h>		//���ڿ��� �ٷ�� ���� ���̺귯�� ���
#include <WinSock2.h>	//�����켭 TCP/IP ��� ���α׷��� �����ϱ� ���� ���

#define BUF_SIZE 1024	//BUF_SIZE �� ��� (int)1024�� ����
#define RLT_SIZE 4		//RLT_SIZE �� ��� (int)4�� ����
#define OPSZ 4			//OPSZ �� ��� (int)4�� ����

//���� �Ʒ� ������ �Լ����� ����ϱ� ���� ����
void ErrorHandling(char *message);	//������ ���� ���ڿ��� ����ϱ� ���� �Լ�

//������ ��� �μ��δ� IPv4(127.0.0.2)�� ��Ʈ(9191)�� ����
int main(int argc, char *argv[]) {

	//���α׷��� Ÿ��Ʋ �̸� ����
	system("title op_client_win 127.0.0.2 9191");

	WSADATA wsaData;	//���� �ʱ�ȭ
	SOCKET hSocket;		//���� ����
	char opmsg[BUF_SIZE];	//����� �� �迭
	int result, opndCnt, i;	//���� ���� �ʱ�ȭ
	SOCKADDR_IN servAdr;	//IPv4 �ּ����� ����ü

	// ���� main�Լ��� ���޵� ������ ���� 3�� �ƴ� ���
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	// ���� ���� �ʱ�ȭ�� �����ϴ� ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error!");//���� ���� ��� �� ���α׷� ����(�����ʱ�ȭ)
	}

	//IPv4 ��������, TCP ����� ����
	hSocket = socket(PF_INET, SOCK_STREAM, 0);

	//���� ���� ������ ������ ���
	if (hSocket == INVALID_SOCKET) {
		ErrorHandling("socket() error");	//���� ���� ��� �� ���α׷� ����(���� ����)
	}

	//�ּҸ� 0���� �ּ��� ���̸�ŭ ����
	memset(&servAdr, 0, sizeof(servAdr));

	//�ּ� ����
	servAdr.sin_family = AF_INET;	//�ּҴ� IPv4 ��������
	servAdr.sin_addr.s_addr = inet_addr(argv[1]);	//�ڽ��� IP�ּҸ� �Ҵ�(main�Լ� ����μ�)
	servAdr.sin_port = htons(atoi(argv[2]));	//�ڽ��� ���α׷� ��Ʈ�� �Ҵ�(main�Լ� ����μ�)

	//�������� ���ӿ� ������ ���
	if (connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR) {
		ErrorHandling("connect() error!");	//���� ���� ��� �� ���α׷� ����(connect ����)
	}
	//�ƴϸ�
	else {
		puts("Connected........."); //����Ǿ��� ǥ��
	}

	//������ ���� ���� �Է� ��û ���
	fputs("Operand count: ", stdout);
	//������ ���� ���� �Է�
	scanf("%d", &opndCnt);
	//opmsg[0]�� ������ ���� ���� ������ ĳ���� ���·� ����
	opmsg[0] = (char)opndCnt;

	//������ ���� ������ŭ ����
	for (i = 0; i < opndCnt; i++) {
		//������ �� �Է� ��û ���
		printf("Operand %d: ", i + 1);
		//������ �� �Է¹����� opmsg[i*OPSZ+1]�� ����
		scanf("%d", (int*)&opmsg[i*OPSZ + 1]);
	}
	fgetc(stdin);
	//����� ������ �Է� ��û ���
	fputs("Operator: ", stdout);
	//����� ������ �Է¹����� opmsg[opndCnt*OPSZ+1]�� ����
	scanf("%c", &opmsg[opndCnt*OPSZ + 1]);
	//������ ������ ������ �۽�
	send(hSocket, opmsg, opndCnt*OPSZ + 2, 0);
	//�����κ��� ���Ź��� ���� ����� result ������ ����
	recv(hSocket, (char*)&result, RLT_SIZE, 0);
	
	//�����κ��� ���Ź��� ���� ����� ���
	printf("Operation result: %d \n", result);
	closesocket(hSocket); // ������ ����
	WSACleanup();	//���� ����
	return 0;	//main�Լ� ��ȯ
}

//�������� ��� �� ���α׷� ���Ḧ ���� �Լ�
void ErrorHandling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}