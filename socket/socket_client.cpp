#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

#define SERV_PORT 9000

int main(int argc, char *const * argv)
{
    //1.创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in claddr;
    memset(&claddr, 0, sizeof(claddr));

    //2.设置服务器所需要的信息
    claddr.sin_family = AF_INET;
    claddr.sin_port = htons(SERV_PORT);
    if(inet_pton(AF_INET, "192.168.1.125", &claddr.sin_addr) <= 0)
    {
        printf("调用inet_pton失败，退出！");
        exit(1);
    }

    //3.建立连接
    if(connect(sockfd, (struct sockaddr*)&claddr,sizeof(claddr)) < 0)
    {
        printf("调用connect失败，退出！");
        exit(1);
    }

    int n;
    char recvline[1000 + 1];
    //4. 接收服务器传来的信息
    while((n = read(sockfd, recvline,1000)) > 0)
    {
        //此处商业代码要检查收到的宽度和是否收取完毕
        recvline[n] = 0;
        printf("收到的内容为：%s\n",recvline);
    }
    close(sockfd);
    printf("程序执行完毕，退出！\n");
    return 0;
}