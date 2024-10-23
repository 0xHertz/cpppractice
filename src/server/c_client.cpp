#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 3000
#define MESSAGE "hello"

int main(int argc, char* argv[]){
    /* 创建socket */
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1) {
        std::cout << "socket error" << std::endl;
        return -1;
    }

    /* connect */
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr  = inet_addr(SERVER_ADDR);
    serveraddr.sin_port = htons(SERVER_PORT);
    if (connect(clientfd, (struct sockaddr * ) &serveraddr, sizeof(serveraddr)) == -1) {
        std::cout << "connect error" << std::endl;
        return -1;
    }

    /* send */
    int ret = send(clientfd, MESSAGE, strlen(MESSAGE), 0);
    if (ret != strlen(MESSAGE)) {
        std::cout << "send error" << std::endl;
        return -1;
    }
    std::cout << "send to server: " << MESSAGE << std::endl;

    /* receive */
    char buf[32] = {0};
    ret = recv(clientfd, buf, sizeof(buf), 0);
    if (ret > 0) {
        std::cout << "receive from server: " << buf << std::endl;
    }else{
        std::cout << "receive error" << std::endl;
    }

    /* close */
    close(clientfd);
    return 0;
}
