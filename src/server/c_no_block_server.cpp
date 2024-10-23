#include <arpa/inet.h>
#include <cerrno>
#include <cstddef>
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <vector>
/* serverfd 设置为非阻塞模式 */
/* clientfd 设置为非阻塞模式 */
/* send connect recv 函数的使用上没有不同，但是表现上会有不同*/
int main(int argc, char* argv[]){
    /* create fd */
    int severfd = socket(AF_INET, SOCK_STREAM, 0);
    // set socket to no block
    int oldseverfdflag = fcntl(severfd, F_GETFL);
    int newseverfdflag = oldseverfdflag | O_NONBLOCK;
    if (fcntl(severfd, F_SETFL,newseverfdflag) == -1) {
        std::cout << "set to no block error" << std::endl;
        close(severfd);
        return -1;
    }

    /* create socket */
    struct sockaddr_in severaddr;
    severaddr.sin_family = AF_INET;
    severaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    severaddr.sin_port = htons(3000);
    socklen_t sever_len = sizeof(severaddr);

    /* bind */
    if (bind(severfd, (struct sockaddr*) &severaddr, sizeof(severaddr)) == -1) {
        std::cout << "bind error" << std::endl;
        close(severfd);
        return -1;
    }

    /* listen */
    if (listen(severfd, SOMAXCONN)) {
        std::cout << "listen error" << std::endl;
        close(severfd);
        return -1;
    }

    /* 设置pollfd数组，存储需要监听的fd，包括服务器fd和客户端fd */
    std::vector<struct pollfd> pollfds;
    pollfds.push_back({severfd,POLLIN,0});

    /* set accept to no block */
    while (true) {
        /* 返回就绪的fd数量 */
        int pull_count = poll(pollfds.data(), pollfds.size(), -1);
        if (pull_count == -1) {
            std::cout << "poll error" << std::endl;
            break;
        }

        /* 遍历fd，如果是severfd，则接收客户端连接，如果是客户端fd，则执行逻辑 */
        for (size_t i = 0; i<pollfds.size(); i++) {
            /* 判断是否为就绪状态 */
            if (pollfds[i].revents & POLLIN) {
                if (pollfds[i].fd == severfd) {
                    /* 服务器准备就绪 */
                    struct sockaddr_in clientaddr;
                    socklen_t clientaddrlen = sizeof(clientaddr);
                    int clientfd = accept(severfd, (struct sockaddr* ) &clientaddrlen, &clientaddrlen);
                    if (clientfd != -1) {
                        int oldclientflag = fcntl(clientfd, F_GETFL);
                        int newclientflag = oldclientflag | O_NONBLOCK;
                        if (fcntl(clientfd, F_SETFL,newclientflag) == -1) {
                            std::cout << "set accept client to no block error" << std::endl;
                            close(clientfd);
                        }else{
                            // 加入pollfds
                            pollfds.push_back({clientfd, POLLIN, 0});
                            std::cout << "Accepted new client: " << clientfd << std::endl;
                        }
                    }
                }else{
                    /* 客户端准备就绪 */
                    char buf[32] = {0};
                    int ret = recv(pollfds[i].fd, buf, 32, 0);
                    // recv 行为上的不同
                    if (ret > 0) {
                        std::cout << "receive from client " << pollfds[i].fd << " : " << buf << std::endl;
                        // send行为上的不同
                        ret = send(pollfds[i].fd, buf, strlen(buf), 0);
                        if (ret == -1) {
                            /* 需要根据状态码进一步判断send状态 */
                            if (errno == EWOULDBLOCK) {
                                std::cout << "client tcp window too small" << std::endl;
                            }else if (errno == EINTR) {
                                std::cout << "recv data interrupted by signal." << std::endl;
                            }else {
                                // 真的出错了
                                std::cout << "send data error." << std::endl;
                                close(pollfds[i].fd);
                                pollfds.erase(pollfds.begin() + i);
                                --i;
                            }
                        }else if (ret == 0) {
                            std::cout << "[send] close by client" << std::endl;
                            close(pollfds[i].fd);
                            pollfds.erase(pollfds.begin() + i);
                            --i;
                        }else {
                            std::cout << "send to client: " << pollfds[i].fd << buf << std::endl;
                        }
                    }else if (ret == 0) {
                        std::cout << "[recv] close by client" << std::endl;
                        close(pollfds[i].fd);
                        pollfds.erase(pollfds.begin() + i);
                        --i;
                    }else if (ret == -1) {
                        /* 需要根据错误信息进一步判断 recv状态 */
                        if (errno == EWOULDBLOCK) {
                            std::cout << "there is no data avaliable now" << std::endl;
                            sleep(3);
                        }else if (errno == EINTR) {
                            // 信号被中断，继续尝试recv
                            std::cout << "recv data interrupted by signal." << std::endl;
                        }else {
                            // 真的出错了
                            std::cout << "recv error on client " << pollfds[i].fd << std::endl;
                            close(pollfds[i].fd);
                            pollfds.erase(pollfds.begin() + i);
                            --i;
                        }
                    }
                }
            }
        }
    }
    close(severfd);
    return 0;
}
