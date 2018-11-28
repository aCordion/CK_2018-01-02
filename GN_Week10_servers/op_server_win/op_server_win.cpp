#pragma comment(lib, "ws2_32")	// ������ ���� ���̺귯��
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>		//ǥ�� ����� ���
#include <stdlib.h>		//���ڿ� ��ȯ�� ���� ǥ�� ���̺귯�� ���
#include <string.h>		//���ڿ��� �ٷ�� ���� ���̺귯�� ���
#include <WinSock2.h>	//�����켭 TCP/IP ��� ���α׷��� �����ϱ� ���� ���

#define BUF_SIZE 1024	//BUF_SIZE �� ��� (int)1024�� ����
#define OPSZ 4			//OPSZ �� ��� (int)4�� ����

//���� �Ʒ� ������ �Լ����� ����ϱ� ���� ����
void ErrorHandling(char * message);	//������ ���� ���ڿ��� ����ϱ� ���� �Լ�
int calculate(int opnum, int opnds[], char oprator);	//����� �����ϱ� ���� �Լ�

//������ ��� �μ��δ� ��Ʈ(9191)�� ����
int main(int argc, char * argv[]) {

	//���α׷��� Ÿ��Ʋ �̸� ����
	system("title op_server_win 9191");

	WSADATA wsaData;	//���� �ʱ�ȭ
	SOCKET hServSock, hClntSock;	//���� ����
	char opinfo[BUF_SIZE];	//����� �� �迭
	int result, opndCnt, i;	//���� ���� �ʱ�ȭ
	int recvCnt, recvLen;	//���� ���� �ʱ�ȭ
	SOCKADDR_IN servAdr, clntAdr;	//IPv4 �ּ����� ����ü
	int clntAdrSize;	//Ŭ���̾�Ʈ �ּ� ũ�⸦ ���� ����

	//���� main�Լ��� ���޵� ������ ���� 2�� �ƴ� ���
	if (argc != 2) {
		printf("Usage  %s <port>\n", argv[0]);	//������ ǥ����
		exit(1);	//���α׷� ����
	}

	//���� ���� ���� 2.2�� �ʱ�ȭ���� ������ �ƴ� ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error!");	//���� ���� ��� �� ���α׷� ����(�����ʱ�ȭ)
	}
	hServSock = socket(PF_INET, SOCK_STREAM, 0);	//���� ������ IPv4 ��������, TCP ����� ����
	
	//���� ���� ���� ������ ������ ���
	if (hServSock == INVALID_SOCKET) {
		ErrorHandling("socket() error");	//���� ���� ��� �� ���α׷� ����(���� ����)
	}
	//���� �ּҸ� 0���� ���� �ּ��� ���̸�ŭ ����
	memset(&servAdr, 0, sizeof(servAdr));

	//������ �ּ� ����
	servAdr.sin_family = AF_INET;	//���� �ּҴ� IPv4 ��������
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);	//��� �ּҿ����� ������ �޾Ƶ���
	servAdr.sin_port = htons(atoi(argv[1]));	//��Ʈ �ּ� (main�Լ��� ����μ�)

	//���� ������ ����Ʈ���� ��Ʈ�� IP�� ���� ���� ������ ���
	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR) {
		ErrorHandling("bind() error");	//���� ���� ��� �� ���α׷� ����(bind ����)
	}

	//Ŭ���̾�Ʈ�� ���� ��û�� ���� ������ ����� ������ ������ ���
	if (listen(hServSock, 5) == SOCKET_ERROR) {
		ErrorHandling("listen() error");	//���� ���� ��� �� ���α׷� ���� (listen ����)
	}

	//Ŭ���̾�Ʈ �ּ� ũ��
	clntAdrSize = sizeof(clntAdr);

	for (i = 0; i < 5; i++) {	//5ȸ ����
		opndCnt = 0;	//���� �ʱ�ȭ
		//Ŭ���̾�Ʈ ������ ������ ���
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSize);
		recv(hClntSock, (char*)&opndCnt, 1, 0);	//�޽����� �����ϴ� �Լ�
		recvLen = 0;	//���� �ʱ�ȭ
		while ((opndCnt*OPSZ + 1) > recvLen) {
			//���� ���� �� ������ ����Ʈ ���� recvCnt ������ ����
			recvCnt = recv(hClntSock, &opinfo[recvLen], BUF_SIZE - 1, 0);
			recvLen += recvCnt;	//recvLen�� recvCnt�� ����
		}
		//Ŭ���̾�Ʈ���� �Է¹��� ������ ����Ͽ� �������� ��� �� ���� result ������ ����
		result = calculate(opndCnt, (int*)opinfo, opinfo[recvLen - 1]);
		send(hClntSock, (char*)&result, sizeof(result), 0);	//�޽��� �۽� �Լ�
		closesocket(hClntSock);	//Ŭ���̾�Ʈ ������ ����
	}
	closesocket(hServSock);	//���� ������ ����
	WSACleanup();	//���� ����
	return 0;	//main�Լ� ��ȯ;
}

//����� ����ϴ� �Լ�
int calculate(int opnum, int opnds[], char op) {

	int result = opnds[0], i;

	switch (op) {
	case '+':
		for (i = 1; i < opnum; i++) {
			result += opnds[i];
		}
		break;
	case '-':
		for (i = 1; i < opnum; i++) {
			result -= opnds[i];
		}
		break;
	case '*':
		for (i = 1; i < opnum; i++) {
			result *= opnds[i];
		}
		break;
	}
	return result;
}

//�������� ��� �� ���α׷� ���Ḧ ���� �Լ�
void ErrorHandling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}