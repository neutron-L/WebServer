#ifndef HTTP_CONN_HH
#define HTTP_CONN_HH

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

/// @brief http连接类，负责处理一个http连接的请求
class HttpConn
{
public:
    // 文件名最大长度和读写缓冲区大小
    static const int kFileNameLen = 256;
    static const int kBufferSize = 2048;

    // http方法，目前只支持GET
    // 采用宏定义的格式命名，和http保持一致
    enum class Method
    {
        GET,
        POST,
        HEAD,
        PUT,
        DELETE,
        TRACE,
        OPTIONS
    };

    // HTTP请求解析的状态
    enum class CheckStatus
    {
        kCheckRequestLine,
        kCheckHeader,
        kCheckContent
    };

    // 返回的状态码
    enum class HttpCode
    {

    };

    // 解析行的状态
    enum class LineStatus
    {
        kLineOk,
        kLineOpen,
        kLineBad
    };

    /* 静态数据成员 */
    // 所有socket上的事件都被注册到同一个epoll内核事件表，I/O线程（主线陈）负责监听
    static int m_epollfd;

private:
    /* 连接相关的成员 */
    // 当前http连接的socket描述符
    int m_sockfd;
    // 对端用户地址 
    sockaddr_in m_address;
    Method m_method;
    char *m_url;
    char *m_host;


    /* 读缓冲区相关的成员 */
    // 读缓冲区
    char m_read_buf[kBufferSize];
    // 下次读取数据的位置
    int m_read_idx;
    // 当前分析的位置
    int m_checked_idx;
    // 当前解析的行的起始位置
    int m_start_line;

    /* 写缓冲区相关的成员 */
    // 写缓冲区
    char m_write_buf[kBufferSize];
    // 下次写入数据的位置
    int m_write_idx;



public:
    HttpConn() = default;
};

#endif