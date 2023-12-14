#ifndef THREADPOOL_HH_
#define THREADPOOL_HH_

#include <iostream>
#include <exception>
#include <semaphore.h>
#include <pthread.h>
#include <queue>

using std::cerr;
using std::cout;
using std::endl;

class Sem
{
private:
    sem_t sem;

public:
    Sem() : Sem(0)
    {
    }
    Sem(unsigned int val)
    {
        if (sem_init(&sem, 0, val) != 0)
        {
            perror("sem_init");
            throw std::exception();
        }
    }

    ~Sem()
    {
        sem_destroy(&sem);
    }

    bool wait()
    {
        return sem_wait(&sem) == 0;
    }

    bool post()
    {
        return sem_post(&sem) == 0;
    }
};

class Locker
{
private:
    pthread_mutex_t lock;

public:
    Locker()
    {
        if (pthread_mutex_init(&lock, NULL) != 0)
        {
            perror("pthread_mutex_init");
            throw std::exception();
        }
    }

    ~Locker()
    {
        pthread_mutex_destroy(&lock);
    }

    bool lock()
    {
        return pthread_mutex_lock(&lock) == 0;
    }

    bool unlock()
    {
        return pthread_mutex_unlock(&lock) == 0;
    }
};

#endif