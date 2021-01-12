#include <cstdlib>
#include <getopt.h>
#include <string>
#include "EventLoop.h"
#include "Server.h"
using std::string;
int main(int argc, char** argv)
{  
    // 线程个数
    int threadNum = 4;
    // 默认端口
    int port = 2222;
    // // 生成 log 文件的地址
    // const char* logSavePath = "./WebServer.log";
    // 终端命令的读取
    // const char* shortopts = "t:l:p:";
    const char* shortopts = "t:p:";
    int opt;
    while ((opt = getopt(argc, argv, shortopts)) != -1)
    {
        switch (opt)
        {
            case 't':
            {
                // atoi() 转译 optarg 所指向的字节字符串中的整数值
                threadNum = atoi(optarg);
                break;
            }
            // case 'l':
            // {
            //     // 这里 optarg 是 char* 类型， logSavePath 是 string 类型
            //     logSavePath = optarg;
            //     break;
            // }
            case 'p':
            {
                port = atoi(optarg);
                break;
            }
        default:
            break;
        }
    }
    printf("------------Server info:-----------------\n");
    printf("The server runs in %d threads at port : %d", threadNum, port);
    
    EventLoop mainLoop;
    Server myHTTPServer(&mainLoop, threadNum, port);
    myHTTPServer.start();
    mainLoop.loop();
    return 0;
}