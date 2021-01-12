#pragma once
#include <sys/epoll.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Channel.h"
#include "HttpData.h"
#include "Timer.h"


class Epoll 
{
    /**
     * epoll 的创建 ： int epoll_create(int size), int epoll_create1(int flag)
     * 创建 epoll 需要一个额外的文件描述符 epollFd_
     * epoll 内核事件的操作： epoll_ctl()
     * epoll 系统调用的主要接口 : epoll_wait() 其在一段时间内等待一组文件描述符上的事件
    */
public:
    Epoll();
    ~Epoll();
    void epoll_add(SP_Channel request, int timeout);
    void epoll_mod(SP_Channel request, int timeout);
    void epoll_del(SP_Channel request);
    std::vector<std::shared_ptr<Channel>> poll();
    std::vector<std::shared_ptr<Channel>> getEventsRequest(int events_num);
    void add_timer(std::shared_ptr<Channel> request_data, int timeout);
    int getEpollFd() { return epollFd_; }
    void handleExpired();

    private:
    static const int MAXFDS = 100000;
    int epollFd_;
    std::vector<epoll_event> events_;
    std::shared_ptr<Channel> fd2chan_[MAXFDS];
    std::shared_ptr<HttpData> fd2http_[MAXFDS];
    // 完成基于小根堆的定时器关闭超时请求。 但目前的代码中 timeout 被赋值的 0。
    TimerManager timerManager_;
};