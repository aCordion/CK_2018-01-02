//201813113 ���ϼ�

#pragma comment(lib, "ws2_32")	// ������ ���� ���̺귯��
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>		//ǥ�� ����� ���
#include <WinSock2.h>	//�����켭 TCP/IP ��� ���α׷��� �����ϱ� ���� ���

#define PORT_NUM 3800	// ���� 3800 �� ��� PORT_NUM�� ����
#define MAXLEN 256	// ���� 256 �� ��� MAXLEN�� ����

struct cal_data {	//cal_data ����ü ����
	int left_num;	//���� �ǿ�����
	int right_num;	//������ �ǿ�����
	char op;		//������
	int result;		//�����
	short int error;	//����
};

//main�� ��� �μ��� 127.0.0.1 �� ��
int main(int argc, char ** argv) {

	//���α׷��� Ÿ��Ʋ �̸� ����
	system("title ucalc_client_win 127.0.0.1");

	SOCKET sockfd;	//���� ����
	WSADATA wsaData;	//���� �ʱ�ȭ
	struct sockaddr_in addr, recvaddr;	//IPv4 �ּ����� ����ü
	struct cal_data sdata;	//������ �ְ� ���� ������ ������ ����ü

	char msg[MAXLEN];	//Ŭ���̾�Ʈ���� ����ڰ� �Է��� ������ �޴� char����
	int left_num;	//���� �ǿ�����
	int right_num;	//������ �ǿ�����
	int addrlen;	//�ּұ���

	char op[2];	//�����ڸ� ������ ����

	// ���� main�Լ��� ���޵� ������ ���� 2�� �ƴ� ���
	if (argc != 2) {
		printf("Usage : %s [ip address]\n", argv[0]);
		return 1;	//main�Լ� ��ȯ
	}

	// ���� ���� �ʱ�ȭ�� �����ϴ� ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
		return 1;	//main�Լ� ��ȯ
	}

	//���� ���� ������ ������ ���
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		return 1;//main�Լ� ��ȯ
	}

	//�ּҸ� 0���� �ּ��� ���̸�ŭ ����
	memset((void*)&addr, 0x00, sizeof(addr));

	//�ּ� ����
	addr.sin_family = AF_INET;	//�ּҴ� IPv4 ��������
	addr.sin_addr.s_addr = inet_addr(argv[1]);	//�ڽ��� IP�ּҸ� �Ҵ�(main�Լ� ����μ�)
	addr.sin_port = htons(PORT_NUM);	//�ڽ��� ���α׷� ��Ʈ�� �Ҵ�(��� PORT_NUM(3800))

	//�ݺ�
	while (true) {
		printf("> ");	//�Է��� �� �ִٴ� �������� ǥ������ Ư����ȣ�� ���
		//msg ������ ������� �Է� ���� ����
		fgets(msg, MAXLEN - 1, stdin);
		//���� �Է� ���� quit�̸�
		if (strncmp(msg, "quit\n", 5) == 0) {
			break;	//�ݺ��� Ż��
		}
		//msg ������ ����� ���� �� ó�� ���ڵ��� left_num��, ���ڰ� �ƴ� ���� op��, �� �������� ������ ���ڵ��� right_num�� ����
		sscanf(msg, "%d%[^0-9]%d", &left_num, op, &right_num);

		//sdata�� ������ 0���� �ʱ�ȭ
		memset((void*)&sdata, 0x00, sizeof(sdata));

		//sdata.left_num�� ���� ȣ��Ʈ ����Ʈ ���� ����� left_num ���� 4����Ʈ ��Ʈ��ũ ����Ʈ ���� ������� ��ȯ �� ����
		sdata.left_num = htonl(left_num);
		//sdata.right_num�� ���� ȣ��Ʈ ����Ʈ ���� ����� right_num ���� 4����Ʈ ��Ʈ��ũ ����Ʈ ���� ������� ��ȯ �� ����
		sdata.right_num = htonl(right_num);
		//sdata.op�� ���� op[0]�� �� ����
		sdata.op = op[0];

		int tmp;	//�ӽ� ���� ������ ����
		//addrlen�� addr���� ���̸� ����
		addrlen = sizeof(addr);
		//tmp�� �������� �۽��� ���������� �̷���������� ���� ������� ����(�����)
		tmp = sendto(sockfd, (char *)&sdata, sizeof(sdata), 0, (struct sockaddr*)&addr, addrlen);
		//addrlen�� recvaddr���� ���̸� ����
		addrlen = sizeof(recvaddr);
		//tmp�� ������ ������ ������ ���������� �̷���������� ���� ������� ����(�����)
		tmp = recvfrom(sockfd, (char *)&sdata, sizeof(sdata), 0, (struct sockaddr*)&recvaddr, &addrlen);
		//������ ���� ������ ���� ������ش�.
		printf("%d %c %d = %d\n", ntohl(sdata.left_num), sdata.op, ntohl(sdata.right_num), ntohl(sdata.result));
	}
	closesocket(sockfd);	//������ ����
	WSACleanup();	//���� �ʱ�ȭ
	return 0;	//main�Լ��� ��ȯ
}