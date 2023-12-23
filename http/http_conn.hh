#ifndef HTTP_CONN_HH
#define HTTP_CONN_HH

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/epoll.h>


/// @brief http连接类，负责处理一个http连接的请求
class HttpConn
{
public:
    // 文件名最大长度和读写缓冲区大小
    static const int kFileNameLen = 256;
    static const int kBufferSize = 2048;

    // http方法，目前只支持GET
    enum class Method
    {
        GET, POST, HEAD, PUT, DELETE, TRACE,OPTIONS
    };

    // HTTP请求解析的状态
    enum class CheckStatus{
        
    };

    // 返回的状态码
    enum class HttpCode {

    };

    // 解析行的状态
    enum class LineStatus {
        
    };
    
};

#endif