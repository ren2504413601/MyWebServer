#ifndef SERVER
#define SERVER

#include <functional>
#include "EventLoop.h"
#include <memory>
#include "Channel.h"
#include "EventLoopThreadPool.h"
class Server
{
public:
    // std::function<void()> 定义于头文件 <functional>
    typedef std::function<void()> Functor;
    Server(EventLoop* loop, int threadNum, int port);
    ~Server(){};
    void start();
    void handNewConn();
    void handThisConn() { loop_->updatePoller(acceptChannel_); }
private:
    EventLoop *loop_;
    int threadNum_;
    std::unique_ptr<EventLoopThreadPool> eventLoopThreadPool_;
    bool started_;
    std::shared_ptr<Channel> acceptChannel_;
    int port_;
    int listenFd_;
    static const int MAXFDS = 100000;
};

#endif