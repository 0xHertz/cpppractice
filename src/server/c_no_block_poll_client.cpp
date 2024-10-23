#include <asm-generic/socket.h>
#include <cerrno>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>

int main() {
    // 创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        return 1;
    }

    // 服务器地址配置
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3000); // 服务器端口
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); // 服务器IP

    // 设置套接字为非阻塞
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    // 尝试连接到服务器
    int ret = connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr));
    if (ret < 0 && errno != EINPROGRESS) {
        std::cerr << "Connection failed!" << std::endl;
        close(sockfd);
        return 1;
    }

    // 使用 poll 进行非阻塞检查
    pollfd fds[1];
    fds[0].fd = sockfd;
    fds[0].events = POLLOUT | POLLIN;

    int poll_ret = poll(fds, 1, 5000); // 超时时间为5000毫秒
    if (poll_ret == -1) {
        std::cerr << "Poll error!" << std::endl;
        close(sockfd);
        return 1;
    } else if (poll_ret == 0) {
        std::cerr << "Connection timeout!" << std::endl;
        close(sockfd);
        return 1;
    } else {
        if (fds[0].revents & POLLOUT) {
            // 还需要进一步检查
            int err;
            socklen_t len = sizeof(err);
            if (getsockopt(fds[0].fd, SOL_SOCKET, SO_ERROR, &err, &len) < 0 ) {
                std::cout << "get clientfd opt error" << std::endl;
                close(sockfd);
                return -1;
            }else if (err == 0) {
                // 连接成功
                std::cout << "[poll] connect to server success" << std::endl;
                // 发送数据
                const char *msg = "Hello, Server!";
                int ret = send(sockfd, msg, strlen(msg), 0);
                if (ret == -1) {
                    /* 需要根据状态码进一步判断send状态 */
                    if (errno == EWOULDBLOCK) {
                        std::cout << "sever tcp window too small" << std::endl;
                    }else if (errno == EINTR) {
                        std::cout << "recv data interrupted by signal." << std::endl;
                    }else {
                        std::cout << "send error." << std::endl;
                        // 真的出错了
                        close(sockfd);
                    }
                }else if (ret == 0) {
                    std::cout << "[send] close by client" << std::endl;
                }else {
                    std::cout << "send to sever: " << msg << std::endl;
                    // 重要，虽然服务器是立刻返回的数据，但是还是稍等一会儿再检查poll
                    sleep(1);
                    // 接收数据
                    int recv_poll_ret = poll(fds, 1, 5000);
                    if (recv_poll_ret > 0 && (fds[0].revents & POLLIN)) {
                        char buffer[1024];
                        memset(buffer, 0, sizeof(buffer));
                        ret = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
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
                    }else {
                        std::cout << "poll time out" << std::endl;
                    }

                }
            }else {
                std::cout << "[select] connect to server error truly" << std::endl;
            }
        }
    }

    // 关闭套接字
    close(sockfd);
    return 0;
}
