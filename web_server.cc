#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdbool>

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

/* 常量定义 */
const int kMaxFd = 65536;
const int kMaxEventNumber = 10000;

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
    return 0;
}
