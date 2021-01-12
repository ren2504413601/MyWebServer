#ifndef EVENT_LOOP
#define EVENT_LOOP

#include <cassert>
#include <functional>
#include <memory>
#include <vector>
#include "MutexLock.h"
#include "Epoll.h"
#include "CurrentThread.h"
#include "Util.h"
class EventLoop
{
public:
	// std::function<void()> 定义于头文件 <functional>
	typedef std::function<void()> Functor;
	EventLoop();
	~EventLoop();
	void loop();
	bool isInLoopThread() const{ return threadId_ == CurrentThread::tid(); };
	void assertInLoopThread() { assert(isInLoopThread()); }
	void quit();
	void runInLoop(Functor&& cb);
  	void queueInLoop(Functor&& cb);
	void shutdown(std::shared_ptr<Channel> channel) { shutDownWR(channel->getFd()); }
	void removeFromPoller(std::shared_ptr<Channel> channel) 
	{
		// shutDownWR(channel->getFd());
		poller_->epoll_del(channel);
	}
	void updatePoller(std::shared_ptr<Channel> channel, int timeout = 0) 
	{
		poller_->epoll_mod(channel, timeout);
	}
	void addToPoller(std::shared_ptr<Channel> channel, int timeout = 0) 
	{
		poller_->epoll_add(channel, timeout);
	}
private:
	int wakeupFd_;
	bool looping_;
	bool quit_;
	bool eventHandling_;
	bool callingPendingFunctors_;
	// shared_ptr 定义于头文件 <memory>
	std::shared_ptr<Epoll> poller_;
	std::shared_ptr<Channel> pwakeupChannel_;
	const pid_t threadId_;
	// pendingFunctors_ 由 EventLoop::queueInLoop()完成赋值
	// EventLoop::queueInLoop() 在 Server::handNewConn() 中被调用
	std::vector<Functor> pendingFunctors_;
	mutable MutexLock mutex_;


	void wakeup();
	void handleRead();
	void doPendingFunctors();
	void handleConn();

};

#endif