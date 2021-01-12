## 语法知识

标准函数库 std::function 类型.参阅 c++ prime 14.8.3 可调用对象与 function


[__thread]关键字(https://blog.csdn.net/xj178926426/article/details/54345449)

这是一种线程局部存储(tls)是一种机制。通过这一机制分配的变量，每个当前线程有一个该变量的实例。

__thread是GCC内置的线程局部存储设施，存取效率可以和全局变量相比。__thread变量每一个线程有一份独立实体，各个线程的值互不干扰。可以用来修饰那些带有全局性且值可能变，但是又不值得用全局变量保护的变量。

[`#pragma once`](https://blog.csdn.net/fanyun_01/article/details/77413992) 的作用

为了避免同一个头文件被包含（include）多次，C/C++中有两种宏实现方式：一种是#ifndef方式；另一种是#pragma once方式。

[mutable](https://www.cnblogs.com/yongdaimi/p/9565996.html) 关键字

在C++中，mutable也是为了突破const的限制而设置的。被mutable修饰的变量，将永远处于可变的状态，即使在一个const函数中。

[explicit关键字](https://blog.csdn.net/guoyunfei123/article/details/89003369)

C++中的explicit关键字只能用于修饰只有一个参数的类构造函数, 它的作用是表明该构造函数是显示的, 而非隐式的, 跟它相对应的另一个关键字是implicit, 意思是隐藏的,类构造函数默认情况下即声明为implicit(隐式)。

 explicit关键字的作用就是防止类构造函数的隐式自动转换。



[std::bind](https://blog.csdn.net/u013654125/article/details/100140328) 的调用格式
```c++
auto newCallable = bind(callable, arg_list);
```
其中，返回值`newCallable`本身是一个可调用对象，`arg_list`是用逗号分割的参数列表，是相对于给定的 `callable`的参数。
即，当我们调用 `newCallable` 的时候，会调用 `callable`， 并传递给它 `arg_list` 的参数。


## 编译
### CMAKE 记录

```shell
mkdir build_folder
cd build_folder
cmake soure_folder
```
这里，source_folder 是包含CMakeLisrs.txt文件的文件夹，是要被cmake 编译的文件。 具体的编译规则是包含在CmakeLists.txt 文件中的。 build_folder 是cmake 编译之后的保存目录。

执行了 cmake 命令之后会发现生成了三个文件，分别是`CMakeFiles, CMake_install.cmake, CMakeCache.txt, Makefile`。根据文件名称大概猜测其作用。这里生成的 Makefile 需要再次 make 然后完成编译。

Cmake 并不支持 make distclean。因为CMakeLists.txt可以执行脚本并通过脚本生成一些临时文件，但是却没有办法来跟
踪这些临时文件到底是哪些。因此，没有办法提供一个可靠的make distclean方案。

### [CMakeFiles.txt](https://www.hahack.com/codes/cmake/) 的书写

PROJECT指令
```shell
PROJECT(projectname [CXX] [C] [Java])
```
可以用这个指令定义工程名称，并可指定工程支持的语言

set 操作用来显式定义变量

```
SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])
```

MESSAGE指令
```
MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display")
```
这个指令用于向终端输出用户定义的信息，包含了三种类型:
SEND_ERROR，产生错误，生成过程被跳过。
SATUS，输出前缀为—的信息。FATAL_ERROR，立即终止所有cmake过程

ADD_EXECUTABLE指令
```
ADD_EXECUTABLE(hello ${SRC_LIST})
```
定义了这个工程会生成一个文件名为hello的可执行文件，相关的源文件是SRC_LIST中
定义的源文件列表

string 操作

```
# 字符串/变量替换
string(REPLACE <match-string> <replace-string> <out-var> <input>...)
```
```
# Convert <string> to lower characters.
string(TOUPPER <string> <output_variable>)
```