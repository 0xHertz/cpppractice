#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <bits/types/struct_timeval.h>
#include <cerrno>
#include <cstddef>
#include <cstring>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 3000
#define MESSAGE "hello server"

int main(int argc, char* argv[]){
    /* 创建socket */
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);

    /* 设置socket为非阻塞模式 */
    // 获取socket文件标志
    int oldclientflag = fcntl(clientfd,F_GETFL);
    int newclientflag = oldclientflag | O_NONBLOCK;
    // 设置socket文件标志
    if (fcntl(clientfd, F_SETFL, newclientflag) == -1) {
        std::cout << "set no block error" << std::endl;
        close(clientfd);
        return -1;
    }

    /* connect */
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    serveraddr.sin_port = htons(SERVER_PORT);
    while (true) {
        int ret = connect(clientfd, (struct sockaddr*) &serveraddr, sizeof(serveraddr));
        if (ret == 0) {
            std::cout << "connect to server successful immediately" << std::endl;
            close(clientfd);
            return 0;
        }else if (ret == -1) {
            if (errno == EINTR) {
                std::cout << "connecting interruptted by signal, try again." << std::endl;
                continue;
            }else if (errno == EINPROGRESS) {
                // 连接正在尝试中
                std::cout << "connnecting..." << std::endl;
                break;
            }else{
                // 真的出错了
                close(clientfd);
                return -1;
            }
        }
    }

    /* select 等函数判断是否连接成功 */
    // 初始化文件描述符集合，并将clientfd加入其中
    fd_set writeset;
    FD_ZERO(&writeset);
    FD_SET(clientfd, &writeset);

    // 可以利用tv_sec和tv_usec实现更小精度的超时控制
    struct timeval tv;
    tv.tv_sec = 3; // 秒
    tv.tv_usec = 0;// 微秒
    if (select(clientfd+1, NULL, &writeset, NULL, &tv) != 1) {
        std::cout << "[select] connect to sever error" << std::endl;
        close(clientfd);
        return -1;
    }
    /* =1还需要进一步判断 */
    int err;
    socklen_t len = sizeof(err);
    if (getsockopt(clientfd, SOL_SOCKET, SO_ERROR, &err, &len) < 0) {
        std::cout << "get clientfd opt error" << std::endl;
        close(clientfd);
        return -1;
    }
    if (err == 0) {
        std::cout << "[select] connect to server success" << std::endl;
        // some other options
        int ret = send(clientfd, MESSAGE, strlen(MESSAGE), 0);
        if (ret == -1) {
            /* 需要根据状态码进一步判断send状态 */
            if (errno == EWOULDBLOCK) {
                std::cout << "sever tcp window too small" << std::endl;
            }else if (errno == EINTR) {
                std::cout << "recv data interrupted by signal." << std::endl;
            }else {
                std::cout << "send error." << std::endl;
                // 真的出错了
                close(clientfd);
            }
        }else if (ret == 0) {
            std::cout << "[send] close by client" << std::endl;
        }else {
            // 接收数据
            char buffer[1024];
            memset(buffer, 0, sizeof(buffer));
            sleep(1);
            ret = recv(clientfd, buffer, sizeof(buffer) - 1, 0);
            if (ret > 0) {
                std::cout << "receive from client " << buffer << std::endl;
            }else if (ret == 0) {
                std::cout << "[recv] close by sever" << std::endl;
            }else if (ret == -1) {
                /* 需要根据错误信息进一步判断 recv状态 */
                if (errno == EWOULDBLOCK) {
                    std::cout << "there is no data avaliable now" << std::endl;
                }else if (errno == EINTR) {
                    // 信号被中断，继续尝试recv
                    std::cout << "recv data interrupted by signal." << std::endl;
                }else {
                    // 真的出错了
                    std::cout << "recv error." << std::endl;
                }
            }
        }
    }else {
        std::cout << "[select] connect to server error truly" << std::endl;
    }


    close(clientfd);
    return 0;
}
