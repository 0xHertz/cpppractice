#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){
    /* 创建监听socket */
    // socket(int domain, int type, int protocol)
    /*
    SOCK_STREAM：面向连接的稳定通信，底层是 TCP 协议，我们会一直使用这个。
    SOCK_DGRAM：无连接的通信，底层是 UDP 协议，需要上层的协议来保证可靠性。
    SOCK_RAW：更加灵活的数据控制，能让你指定 IP 头部 */
    int listendfd = socket(AF_INET, SOCK_STREAM, 0);

    /* bind ip and port */
    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(3000);
    if( bind(listendfd,(struct sockaddr*)&bindaddr,sizeof(bindaddr)) == -1){
        std::cout << "bind listen socket error" << std::endl;
        close(listendfd);
        return -1;
    }

    /* listen */
    if (listen(listendfd, SOMAXCONN)) {
        std::cout << "listen error" << std::endl;
        close(listendfd);
        return -1;
    }


    /* accept */
    while (true) {
        // 接受客户端连接
        struct sockaddr_in clientaddr;
        socklen_t clientaddrlen = sizeof(clientaddr);
        int clifd = accept(listendfd, (struct sockaddr*) &clientaddr, &clientaddrlen);
        if (clifd != -1) {
            while (true) {
                char buf[32] = {0};
                int ret = recv(clifd, buf, 32, 0);
                if (ret > 0) {
                    std::cout << "receive from client: " << buf << std::endl;
                    ret = send(clifd, buf, strlen(buf), 0);
                    if (ret == strlen(buf)) {
                        std::cout << "send to client: " << buf << std::endl;
                    }else{
                        std::cout << "send data error" << std::endl;
                    }
                }else{
                    std::cout << "receive data error" << std::endl;
                    return -1;
                }
            }
        }
    }
    close(listendfd);
    return 0;
}
