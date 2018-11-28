//201813113 ���ϼ�

#pragma comment(lib, "ws2_32")	// ������ ���� ���̺귯��
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>		//ǥ�� ����� ���
#include <WinSock2.h>	//�����켭 TCP/IP ��� ���α׷��� �����ϱ� ���� ���

#define DEBUG			// DEBUG Build
#define PORT_NUM 3800	// ���� 3800 �� ��� PORT_NUM�� ����

struct cal_data {	//cal_data ����ü ����
	int left_num;	//���� �ǿ�����
	int right_num;	//������ �ǿ�����
	char op;		//������
	int result;		//�����
	short int error;	//����
};

int main(int argc, char ** argv) {

	//���α׷��� Ÿ��Ʋ �̸� ����
	system("title ucalc_server_win");

	SOCKET sockfd;	//���� ����
	int addrlen;	//�ּ��� ���̸� ������ ���� ����
	int cal_result;	//���� ������� ������ ���� ����
	int left_num, right_num;	//����, ������ �ǿ����ڸ� ������ ���� ����
	struct sockaddr_in addr, cliaddr;	//IPv4 �ּ����� ����ü
	struct cal_data rdata;	//Ŭ���̾�Ʈ�� �ְ� ���� ������ ������ ����ü

	WSADATA wsaData;	//���� �ʱ�ȭ

	//���� ���� ���� 2.2�� �ʱ�ȭ���� ������ �ƴ� ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
		return 1;	//main�Լ� ��ȯ
	}

	//���� ���� ���� ������ ������ ���
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		return 1;	//main�Լ� ��ȯ
	}
	//���� �ּҸ� 0���� ���� �ּ��� ���̸�ŭ ����
	memset((void*)&addr, 0x00, sizeof(addr));

	//������ �ּ� ����
	addr.sin_family = AF_INET;	//���� �ּҴ� IPv4 ��������
	addr.sin_addr.s_addr = htonl(INADDR_ANY);	//��� �ּҿ����� ������ �޾Ƶ���
	addr.sin_port = htons(PORT_NUM);	//��Ʈ �ּ� (��� PORT_NUM�� �� (3800))

	//�ּ��� ũ��
	addrlen = sizeof(addr);

	//���� ������ ����Ʈ���� ��Ʈ�� IP�� ���� ���� ������ ���
	if (bind(sockfd, (struct sockaddr *)&addr, addrlen) == -1) {
		return 1;	//main�Լ� ��ȯ
	}

	//�ݺ�
	while (true) {
		//Ŭ���̾�Ʈ �ּ��� ũ��
		addrlen = sizeof(cliaddr);
		//Ŭ���̾�Ʈ�� ���� rdata(cal_data ����ä)�� ���� ����
		recvfrom(sockfd, (char*)&rdata, sizeof(rdata), 0, (struct sockaddr*)&cliaddr, &addrlen);

#ifdef DEBUG	//���� �� ���尡 DEBUG�� ����� ���¶��
		//Ŭ���̾�Ʈ�� �ּҿ� ��Ʈ ������ ������ ���, �ٹٲ�
		printf("info : %s (%d)\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
		//Ŭ���̾�Ʈ���� ���� ���� �ǿ�����, ������, ������ �ǿ����ڸ� ���, �ٹٲ�
		printf("%d %c %d\n", ntohl(rdata.left_num),rdata.op, ntohl(rdata.right_num));
#endif	// ifdef DEBUG�� ��
		//��Ʈ��ũ ����Ʈ ���� ����� 4����Ʈ �������� rdata.left_num���� ȣ��Ʈ ����Ʈ ���� ������� left_num������ ����
		left_num = ntohl(rdata.left_num);
		//��Ʈ��ũ ����Ʈ ���� ����� 4����Ʈ �������� rdata.right_num���� ȣ��Ʈ ����Ʈ ���� ������� right_num������ ����
		right_num = ntohl(rdata.right_num);

		//rdata.op���� ���� switch ���
		switch (rdata.op) {
		case '+':	//���� rdata.op�� char���� '+'�̸�
			//cal_result���� left_num�� right_num�� ���� ���� ����
			cal_result = left_num + right_num;
			break;	//switch ��� Ż��
		case '-':	//���� rdata.op�� char���� '-'�̸�
			//cal_result���� left_num�� right_num�� �� ���� ����
			cal_result = left_num - right_num;
			break;	//switch ��� Ż��
		case '*':	//���� rdata.op�� char���� '*'�̸�
			//cal_result���� left_num�� right_num�� ���� ���� ����
			cal_result = left_num * right_num;
			break;	//switch ��� Ż��
		case '/':	//���� rdata.op�� char���� '/'�̸�
			//���� right_num�� 0�̶��
			if (right_num == 0) {
				//rdata.error�� ȣ��Ʈ ����Ʈ ���� ����� 2����Ʈ �������� 2�� ��Ʈ��ũ ����Ʈ ���� ������� ����
				rdata.error = htons(2);
				break;	//switch ��� Ż��
			}
			//cal_result���� left_num�� right_num�� ���� ���� ����
			cal_result = left_num / right_num;
			break;	//switch ��� Ż��
		}
		//rdata.result�� ȣ��Ʈ ����Ʈ ���� ����� 4����Ʈ �������� car_result�� ��Ʈ��ũ ����Ʈ ���� ������� ����
		rdata.result = htonl(cal_result);
		//Ŭ���̾�Ʈ���� ����� ���� rdara ����ü�� ����
		sendto(sockfd, (char*)&rdata, sizeof(rdata), 0, (struct sockaddr*)&cliaddr, addrlen);
	}
	closesocket(sockfd);	//������ ����
	WSACleanup();	//���� �ʱ�ȭ
	return 0;	//main�Լ� ��ȯ
}