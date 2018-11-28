//201813113 ���ϼ�

#pragma comment(lib, "ws2_32")	// ������ ���� ���̺귯��
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>		//ǥ�� ����� ���
#include <stdlib.h>		//���ڿ� ��ȯ�� ���� ǥ�� ���̺귯�� ���
#include <string.h>		//���ڿ��� �ٷ�� ���� ���̺귯�� ���
#include <WinSock2.h>	//�����켭 TCP/IP ��� ���α׷��� �����ϱ� ���� ���

#define BUF_SIZE 30		//������ 30�� ��� BUF_SIZE�� ����

//���� �Ʒ� ������ �Լ����� ����ϱ� ���� ����
void ErrorHandling(char * message);	//������ ���� ���ڿ��� ����ϱ� ���� �Լ�

//������ ��� �μ��δ� ��Ʈ(9190)�� ����
int main(int argc, char * argv[]) {

	//���α׷��� Ÿ��Ʋ �̸� ����
	system("title uecho_server_win 9190");

	WSADATA wsaData;	//���� �ʱ�ȭ
	SOCKET servSock;	//���� ����
	char message[BUF_SIZE];	//�޽����� ������ ����
	int strLen;	//�������� �ʱ�ȭ
	int clntAdrSz;	//Ŭ���̾�Ʈ �ּ�ũ�⸦ ������ ����

	SOCKADDR_IN servAdr, clntAdr;	//IPv4 �ּ����� ����ü

	//���� main�Լ��� ���޵� ������ ���� 2�� �ƴ� ���
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);	//������ ǥ����
		exit(1);	//���α׷� ����
	}

	//���� ���� ���� 2.2�� �ʱ�ȭ���� ������ �ƴ� ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error!");	//���� ���� ��� �� ���α׷� ����(�����ʱ�ȭ)
	}

	//���� ������ IPv4 ��������, UDP ����� ����
	servSock = socket(PF_INET, SOCK_DGRAM, 0);

	//���� ���� ���� ������ ������ ���
	if (servSock == INVALID_SOCKET) {
		ErrorHandling("UDP socket creation error");	//���� ���� ��� �� ���α׷� ����(���� ����)
	}

	//���� �ּҸ� 0���� ���� �ּ��� ���̸�ŭ ����
	memset(&servAdr, 0, sizeof(servAdr));

	//������ �ּ� ����
	servAdr.sin_family = AF_INET;	//���� �ּҴ� IPv4 ��������
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);	//��� �ּҿ����� ������ �޾Ƶ���
	servAdr.sin_port = htons(atoi(argv[1]));	//��Ʈ �ּ� (main�Լ��� ����μ�)

	//���� ������ ����Ʈ���� ��Ʈ�� IP�� ���� ���� ������ ���
	if (bind(servSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR) {
		ErrorHandling("bind() error");	//���� ���� ��� �� ���α׷� ����(bind ����)
	}

	while (true) {
		clntAdrSz = sizeof(clntAdr);	//Ŭ���̾�Ʈ �ּ� ũ��
		//Ŭ���̾�Ʈ�κ��� �޽����� ���Ź���
		strLen = recvfrom(servSock, message, BUF_SIZE, 0, (SOCKADDR*)&clntAdr, &clntAdrSz);
		//Ŭ���̾�Ʈ���� �޽����� ������
		sendto(servSock, message, strLen, 0, (SOCKADDR*)&clntAdr, sizeof(clntAdr));
	}
	closesocket(servSock);	//������ ����
	WSACleanup();	//���� �ʱ�ȭ
	return 0;	//main�Լ� ��ȯ
}

//�������� ��� �� ���α׷� ���Ḧ ���� �Լ�
void ErrorHandling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}