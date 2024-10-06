#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

int main(void)
{
    int ret = 0;
    int client_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(client_sock < 0) {
        perror("socket fail");
        return -1;
    }

    struct sockaddr_in client_addr;
    memset(&client_addr,0,sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    client_addr.sin_port = htons(9999);
    ret = connect(client_sock,(struct sockaddr*)&client_addr,sizeof(client_addr));
    if(ret < 0) {
        perror("connect fail");
        close(client_sock);
        return -1;
    }

    char writebuff[] = "hello server!!!!";
    write(client_sock,writebuff,sizeof(writebuff));
    
    close(client_sock);    
    return 0;
}