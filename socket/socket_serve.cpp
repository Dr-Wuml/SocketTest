#include<stdio.h>
#include<ctype.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>

#define SERV_PORT 9000
int main(int argc,char *const* argv)
{
    //1. 创建套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));

    //设置服务器监听的端口号和ip
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //2. 绑定端口号
    bind(listenfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    
    //3. 监听端口
    listen(listenfd, 32);
    
    int connfd;
    const char *pcontent = "I sent sth to clinet!";

    for(;;)
    {
        //4. 循环监听创建socket
        connfd = accept(listenfd, (struct sockaddr *)NULL,NULL);

        //5. 发送数据write
        write(connfd, pcontent, strlen(pcontent));

        //6. 关闭套接字connfd
        close(connfd);
    } 
    close(listenfd);
    return 0;
}