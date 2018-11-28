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

//������ ��� �μ��δ� IPv4(127.0.0.1)�� ��Ʈ(9190)�� ����
int main(int argc, char * argv[]) {

	//���α׷��� Ÿ��Ʋ �̸� ����
	system("title uecho_client_win 127.0.0.1 9190");

	WSADATA wsaData;	//���� �ʱ�ȭ
	SOCKET sock;		//���� ����	
	char message[BUF_SIZE];	//������ �۽��� ���ڸ� ������ ����
	int strLen;			//���� ���� �ʱ�ȭ

	SOCKADDR_IN servAdr;	//IPv4 �ּ����� ����ü

	// ���� main�Լ��� ���޵� ������ ���� 3�� �ƴ� ���
	if (argc != 3) {
		printf("Usage : %s<IP> <port>\n", argv[0]);
		exit(1);
	}

	// ���� ���� �ʱ�ȭ�� �����ϴ� ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error!");
	}

	//IPv4 ��������, UDP ����� ����
	sock = socket(PF_INET, SOCK_DGRAM, 0);

	//���� ���� ������ ������ ���
	if (sock == INVALID_SOCKET) {
		ErrorHandling("socket() error");
	}

	//�ּҸ� 0���� �ּ��� ���̸�ŭ ����
	memset(&servAdr, 0, sizeof(servAdr));

	//�ּ� ����
	servAdr.sin_family = AF_INET;	//�ּҴ� IPv4 ��������
	servAdr.sin_addr.s_addr = inet_addr(argv[1]);	//�ڽ��� IP�ּҸ� �Ҵ�(main�Լ� ����μ�)
	servAdr.sin_port = htons(atoi(argv[2]));	//�ڽ��� ���α׷� ��Ʈ�� �Ҵ�(main�Լ� ����μ�)
	
	//������ ����
	connect(sock, (SOCKADDR*)&servAdr, sizeof(servAdr));

	//�ݺ�
	while (true) {
		//������ �۽��� ���ڿ��� �Է¹޴� �ȳ��� ���
		fputs("Insert message(q to quit): ", stdout);

		//������ �۽��� �Է¹��� ���ڿ��� message ������ ����
		fgets(message, sizeof(message), stdin);

		//���� q �� Q�� �ܵ����� �Է��ϰ� ���͸� ������ ��� �ݺ� ����� Ż��
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
			break;
		}

		//message������ ����� ���ڿ� �޽����� �۽�
		send(sock, message, strlen(message), 0);

		//�������� �۽��� �޽����� �����ϰ�, �� ����Ʈ ���� strLen�� ����
		strLen = recv(sock, message, sizeof(message) - 1, 0);

		message[strLen] = 0;	//���ڿ��� �������� 0�� ����
		printf("Message from server: %s", message);	//���Ź��� �޽����� ����Ѵ�.
	}
	closesocket(sock);	//������ �ݴ´�
	WSACleanup();	//���� ����
	return 0;	//main �Լ� ��ȯ
}

//�������� ��� �� ���α׷� ���Ḧ ���� �Լ�
void ErrorHandling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}