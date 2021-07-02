//다음과 같은 webpage 배열을 전송하는 웹서버를 구현하라

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/sendfile.h>
#include<fcntl.h>
#define TRUE 1

char webpage[] = "HTTP/1.1 200 OK\r\n" //상태라인
"Server:Linux Web Server\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n" //메세지더
"<!DOCKTYPE html>\r\n" //웹브라우저에 HTML5로 작성된 문서임을 알림
"<html><head><title> My Web Page </title>\r\n"
"<style>body {background-color: #FFFF00 }</style></head>\r\n"
"<body><center><h1>Hello World!</h1><br>\r\n"
"<img src=\"mountain.jpg\"></center></body></html>\r\n";


int main(int argc, char* argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t sin_len = sizeof(clnt_addr);
    int fdimg;
    int option = TRUE;
    char buf[2048];
    char img_buf[700000];

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int)); //주소 재할당
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        perror("bind() error!");
    if (listen(serv_sock, 5) == -1)
        perror("listen() error!");

    while (1)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &sin_len);
        puts("New client connection....");
        read(clnt_sock, buf, 2047);
        printf("%s\n", buf);

        if (!strncmp(buf, "GET /mountain.jpg", 12))
        {
            fdimg = open("mountain.jpg", O_RDONLY);

            //read-write 함수를 통한 구현
            read(fdimg, img_buf, sizeof(img_buf));
            write(clnt_sock, img_buf, sizeof(img_buf));
            close(fdimg);
        }
        else
        {
            write(clnt_sock, webpage, sizeof(webpage) - 1);
            puts("Closing...");
        }
    }
    close(clnt_sock);
    close(serv_sock);
    return 0;
}