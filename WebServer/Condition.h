#pragma once
#include <errno.h>
#include <pthread.h>
#include <pthread.h>
#include <time.h>
#include <cstdint>
#include "MutexLock.h"
#include "noncopyable.h"


class Condition : noncopyable 
{
public:
    /**
     * 动态方式创建条件变量
     * 创建条件变量 pthread_cond_t cond
     * 条件等待     pthread_cond_wait()
     * 激发         pthread_cond_signal()
     * 销毁         pthread_cond_destroy()
    */
    explicit Condition(MutexLock &_mutex) : mutex(_mutex) 
    {
        pthread_cond_init(&cond, NULL);
    }
    ~Condition() { pthread_cond_destroy(&cond); }
    void wait() { pthread_cond_wait(&cond, mutex.get()); }
    void notify() { pthread_cond_signal(&cond); }
    void notifyAll() { pthread_cond_broadcast(&cond); }
    bool waitForSeconds(int seconds) 
    {
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += static_cast<time_t>(seconds);
        return ETIMEDOUT == pthread_cond_timedwait(&cond, mutex.get(), &abstime);
    }

private:
    MutexLock &mutex;
    pthread_cond_t cond;
};