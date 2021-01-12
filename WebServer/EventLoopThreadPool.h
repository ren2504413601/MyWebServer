#pragma once
#include <memory>
#include <vector>
#include "EventLoopThread.h"
#include "noncopyable.h"


class EventLoopThreadPool : noncopyable 
{
    /**
     * 线程池
    */
public:
    EventLoopThreadPool(EventLoop* baseLoop, int numThreads);

    ~EventLoopThreadPool() { printf( "~EventLoopThreadPool()"); }
    void start();

    // Round Robin 轮流选取方法的体现
    EventLoop* getNextLoop();

private:
    EventLoop* baseLoop_;
    bool started_;
    int numThreads_;
    int next_;
    std::vector<std::shared_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_;
};