#ifndef THREADPOOL_HH_
#define THREADPOOL_HH_

#include <iostream>
#include <exception>
#include <pthread.h>
#include <vector>
#include <queue>

#include "locker.hh"

using std::cout;
using std::cerr;
using std::endl;

/// @brief 线程池类
/// @tparam T 线程池中维护的工作队列中的待处理任务类型，需要提供某些接口供线程调用
template <typename T>
class ThreadPool
{
private:
    uint32_t m_thread_number{};       // 线程数
    uint32_t m_max_requests{};        // 待处理的最大任务数
    std::vector<pthread_t> m_threads{};   // 线程数组
    std::queue<T *> m_jobqueue{};     // 工作队列
    Locker m_queue_locker{};
    Semaphore has_job{};           // 信号量——是否有任务加入工作队列
    bool running{};   // 线程池是否正在运行
public:
    ThreadPool(uint32_t nb_threads = 5, uint32_t max_nb_requests = 100) 
    :m_thread_number(nb_threads), m_max_requests(max_nb_requests), m_threads(nb_threads)
    {
        for (int i = 0; i < nb_threads; ++i)
        {
            if (pthread_create(&m_threads[i], NULL, worker, this) != 0 || pthread_detach(m_threads[i]))
            {
                throw std::exception();
            }
        }
        running = true;
    }

    ~ThreadPool()
    {
        running = false;
    }

    bool append(T * job)
    {

    }

};


#endif