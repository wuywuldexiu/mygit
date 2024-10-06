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
    int server_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(server_sock < 0) {
        perror("socket fail");
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(9999);
    ret = bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(ret < 0) {
        perror("bind fail");
        close(server_sock);
        return -1;
    }

    ret = listen(server_sock,5);
    if(ret < 0) {
        perror("listen fail");
        close(server_sock);
        return -1;        
    }

    struct sockaddr_in client_addr;
    memset(&client_addr,0,sizeof(client_addr));
    socklen_t client_len = sizeof(client_addr);
    int client_sock = accept(server_sock,(struct sockaddr*)&client_addr,&client_len);
    if(client_sock < 0) {
        perror("accept fail");
        close(server_sock);
        return -1; 
    }

    char recvbuff[1024];
    ret = read(client_sock,recvbuff,sizeof(recvbuff));
    if(ret < 0) {
        perror("read fail");
        close(client_sock);
        close(server_sock);
        return -1; 
    }
    printf("recv from client:%s\n",recvbuff);

    close(client_sock);
    close(server_sock);
    return 0;
}