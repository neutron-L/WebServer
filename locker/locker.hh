#ifndef THREADPOOL_HH_
#define THREADPOOL_HH_

#include <iostream>
#include <exception>
#include <semaphore.h>
#include <queue>

using std::cout;
using std::cerr;
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
            throw std::exception();
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


#endif