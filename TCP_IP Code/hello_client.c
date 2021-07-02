/*

	-네트워크 프로그래밍 : 서로 다른 두 컴퓨터가 데이터를 주고 받을 수 있도록 하는 것
	-소켓 : 물리적으로 연결된 네트워크 상에서의 데이터 송수신에 사용할 수 있는 소프트웨어적인 장치

	-server에 관련된 함수 : 1~4 순서대로 진행
	1. socket(); 전화기, 소켓이 없으면 인터넷 통신 불가능(인터넷을 할 게 아니면 필요X)
	2. bind(); 전화번호/ip주소와 port번호 할당
	3. listen(); 개통/연결요청 가능 상태로 변경
	4. accept(); 통화/연결요청 수락

	port : 프로그램의 전화번호
	ip : 컴퓨터의 전화번호

	-파일 디스크립터 : 시스템으로부터 할당받은 파일 또는 소켓에 부여된 정수
	0 : 표준입력
	1 : 표준출력
	2 : 표준에러

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char* message);

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len;

	if (argc != 3)
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error!");

	str_len = read(sock, message, sizeof(message) - 1);
	if (str_len == -1)
		error_handling("read() error!");

	printf("Message from server : %s \n", message);
	close(sock);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}