## 简介
本项目拟使用C++实现简单的 Web server。并发模型为Reactor+非阻塞IO+线程池，新连接Round Robin分配。 在搭建好之后使用 WebBench 做 HTTP 的链接测试

## 环境
OS : WSL2 ubuntu 20.04

Compiler: g++ 9.3.0

## 核心技术
- EventLoop 模块。 Reactor 结构完成将 IO 复用拿到的 IO 事件分发给给个文件描述符 (fd)的事件处理函数。由 EventLoop、Channel、Epoll三大类组成

    - EventLoop 类： one loop per thread. 每个线程只能有一个 EventLoop 对象。

    - Channel 类 ： 每个 channel 对象自始都只属于某一个 IO 线程。Channel 会把不同的 IO 事件分发为不同的回调， 例如readHandler 、writeHandler 等。

    - Epoll : 使用 Epoll 边沿触发 (ET) 的IO多路复用技术，非阻塞IO。 
    
    ??????Epoll使用[EPOLLONESHOT](https://blog.csdn.net/liuhengxiao/article/details/46911129)保证一个socket连接在任意时刻都只被一个线程处理
    
- Timer: 由 TimeNode、TimeCamp、TimeManger三个类组成。 完成基于小根堆的定时器关闭超时请求


- Server 模块
    - 使用线程池[EventLoopThreadPool]提高并发度，并降低频繁创建线程的开销 
    
    **？？？？？这块线程池的实现可能要结合互斥锁及条件变量，使用[线程池](https://blog.csdn.net/weixin_40271838/article/details/79998327)之后并发度如何提高及线程创建开销为啥减少暂时还没有搞清楚，可以阅读<<Linux 高性能服务器编程>> 15章的内容，后续会完善**
    - 使用[RAII手法](https://www.jianshu.com/p/b7ffe79498be)封装互斥器[MutexLock类]、 条件变量[Condition类]等线程同步互斥机制，使用RAII管理文件描述符等资源。
    - 使用shared_ptr、weak_ptr管理指针，防止内存泄漏


其中 EventLoop 类的实现方法借鉴了 [WebServer](https://github.com/linyacool/WebServer) 和陈硕的 [muduo](https://github.com/chenshuo/muduo)。


## 使用方法

WebServer 的编译
```shell
# 使用 make 命令
cd WebServer
make clean && make
# 使用 cmake 命令
mkdir build
cd build
cmake ..
```

WebServer 的运行
```
./main
```
## 在另一终端下的测试
```
./stress_client 127.0.0.1 2222 100
```

[WebBench](http://home.tiscali.cz/~cz210552/webbench.html) 的HTTP 长连接的测试

Webbench是一个在linux下使用的非常简单的网站压测工具。它使用fork()模拟多个客户端同时访问我们设定的URL，测试网站在压力下工作的性能，最多可以模拟3万个并发连接去测试网站的负载能力。
```shell
git clone https://github.com/EZLippi/WebBench.git
cd WebBench
sudo make && sudo make install PREFIX=your_path_to_webbench
./bin/webbench -t 60 -c 1000 -2 --get  http://www.baidu.com/
./bin/webbench -t 60 -c 100 -2 --get  http://localhost:2222/
```




