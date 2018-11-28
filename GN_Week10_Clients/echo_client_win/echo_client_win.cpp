#pragma comment(lib, "ws2_32")	// ������ ���� ���̺귯��
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>		//ǥ�� ����� ���
#include <stdlib.h>		//���ڿ� ��ȯ�� ���� ǥ�� ���̺귯�� ���
#include <string.h>		//���ڿ��� �ٷ�� ���� ���̺귯�� ���
#include <WinSock2.h>	//�����켭 TCP/IP ��� ���α׷��� �����ϱ� ���� ���

#define BUF_SIZE 1024	//BUF_SIZE �� ��� (int)1024�� ����

//���� �Ʒ� ������ �Լ����� ����ϱ� ���� ����
void ErrorHandling(char *message);	//������ ���� ���ڿ��� ����ϱ� ���� �Լ�

//������ ��� �μ��δ� IPv4(127.0.0.1)�� ��Ʈ(9190)�� ����
int main(int argc, char * argv[]) {

	//���α׷��� Ÿ��Ʋ �̸� ����
	system("title echo_client_win 127.0.0.1 9190");

	WSADATA wsaData;	//���� �ʱ�ȭ
	SOCKET hSocket;		//���� ����
	char message[BUF_SIZE];	//�޽��� �迭
	int strLen;	//���� ���� �ʱ�ȭ
	SOCKADDR_IN servAdr;	//IPv4 �ּ����� ����ü

	// ���� main�Լ��� ���޵� ������ ���� 3�� �ƴ� ���
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);	//������ ǥ����
		exit(1);	//���α׷� ����
	}

	//���� ���� ���� 2.2�� �ʱ�ȭ���� ������ �ƴ� ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error!");	//���� ���� ��� �� ���α׷� ����(�����ʱ�ȭ)
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
	//����
	while (true) {
		//���ڿ��� �Է¹޴´�.
		fputs("input message(Q to quit): ", stdout);
		//�Է¹��� ���ڿ��� message������ �����Ѵ�
		fgets(message, BUF_SIZE, stdin);

		//���� q �� Q�� �ܵ����� �Է��ϰ� ���͸� ������ ��� ������ Ż���Ѵ�
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
			break;
		}
		
		//������ �Է¹��� �޽����� �۽��Ѵ�.
		send(hSocket, message, strlen(message), 0);
		//�������� �۽��� �޽����� �����ϰ�, �� ����Ʈ ���� strLen�� �����Ѵ�
		strLen = recv(hSocket, message, BUF_SIZE - 1, 0);
		message[strLen] = 0;	//���ڿ��� �������� 0�� ����
		printf("Message from server: %s", message);	//���Ź��� �޽����� ����Ѵ�.
	}

	closesocket(hSocket);	//������ �ݴ´�
	WSACleanup();	//���� ����
	return 0;	//main �Լ� ��ȯ
}

//�������� ��� �� ���α׷� ���Ḧ ���� �Լ�
void ErrorHandling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}