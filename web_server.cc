#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdbool>
#include <map>

#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

#include "locker.hh"
#include "threadpool.hh"
#include "http_conn.hh"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::map;

/* 常量定义 */
const int kMaxFd = 65536;
const int kMaxEventNumber = 10000;
const int kPort = 8080;

/* 使用到的定义在其他文件（http_conn.cc）中的函数 */
extern int addfd(int epollfd, int fd, bool one_shot);
extern int removefd(int epollfd, int fd);

/* helper函数 */
static void addsig(int sig, void (*handler)(int), bool restart = true)
{
    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_flags = restart ? SA_RESTART : 0;
    sigfillset(&sa.sa_mask);
    sa.sa_handler = handler;
    assert(sigaction(sig, &sa, NULL) == 0);
}

static void show_error(int connfd, const char *info)
{
    std::cerr << info << endl;
    send(connfd, info, strlen(info), 0);
}

int main(int argc, char **argv)
{
    // ignore SIGPIPE
    addsig(SIGPIPE, SIG_IGN);

    // 创建一个线程池
    ThreadPool<HttpConn> * pool{nullptr};
    try
    {
        pool= new ThreadPool<HttpConn>();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
    
    // 根据连接描述符查询对应的HttpConn对象
    map<int, HttpConn> dict{};

    // 创建服务器监听端口
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd > 0);
    struct linger tmp = {1, 0};
    setsockopt(listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    inet_pton(AF_INET, "localhost", &address.sin_addr);
    address.sin_port = htons(kPort);

    assert(bind(listenfd, (struct sockaddr *)&address, sizeof(address)) == 0);
    assert(listen(listenfd, 5) == 0);

    // 创建epoll描述符
    epoll_event events[kMaxEventNumber];
    int epollfd = epoll_create(5);
    assert(epollfd > 0);

    // 往epoll事件表中注册监听描述符上的事件
    addfd(epollfd,listenfd, false);

    int ret{};
    int sockfd{};
    while (true)
    {
        ret = epoll_wait(epollfd, events, kMaxEventNumber, -1);

        if (ret < 0 && errno == EINTR)
        {
            perror("epoll");
            break;
        }

        for (int i = 0; i < ret; ++i)
        {
            sockfd = events[i].data.fd;
            // 处理新的连接请求
            if (sockfd == listenfd)
            {

            }
            else 
            {
                HttpConn conn = dict[sockfd];
            }
        }
    }
    return 0;
}
