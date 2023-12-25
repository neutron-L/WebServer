#ifndef THREADPOOL_HH_
#define THREADPOOL_HH_

#include <iostream>
#include <exception>
#include <pthread.h>
#include <vector>
#include <queue>

#include "locker.hh"

using std::cerr;
using std::cout;
using std::endl;

/// @brief 线程池类
/// @tparam T 线程池中维护的工作队列中的待处理任务类型，需要提供某些接口供线程调用
template <typename T>
class ThreadPool
{
private:
    uint32_t m_thread_number{};         // 线程数
    uint32_t m_max_requests{};          // 待处理的最大任务数
    std::vector<pthread_t> m_threads{}; // 线程数组
    std::queue<T *> m_jobqueue{};       // 工作队列
    Locker m_queue_locker{};
    Semaphore has_job{}; // 信号量——是否有任务加入工作队列
    bool running{};      // 线程池是否正在运行
public:
    ThreadPool(uint32_t nb_threads = 5, uint32_t max_nb_requests = 100)
        : m_thread_number(nb_threads), m_max_requests(max_nb_requests), m_threads(nb_threads)
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

    bool append(T *job)
    {
        m_queue_locker.acquire();
        if (m_jobqueue.size() == m_max_requests)
        {
            m_queue_locker.release();
            return false;
        }
        m_jobqueue.push(job);
        m_queue_locker.release();
        return true;
    }

    T *pull_job()
    {
        T *job{NULL};

        m_queue_locker.acquire();
        if (!m_jobqueue.empty() || !())
        {
            job = m_jobqueue.front()
                      m_jobqueue.pop_front();
        }
        m_queue_locker.release();
        return job;
    }

    void * worker(void *arg)
    {
        ThreadPool * pool = static_cast<ThreadPool *>(arg);
        pool->run();

        return NULL;
    }

    void stop()
    {
        running = false;
    }

    void run()
    {
        while (running)
        {
            has_job.wait();
            T * job = pull_job();
            if (job)
                job->process();
        }
    }
};

#endif