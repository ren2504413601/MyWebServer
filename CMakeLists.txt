# cmake 最低版本号要求
cmake_minimum_required(VERSION 2.8)

# 项目信息
project(WebServer CXX)

# 如果没有指定 build type 默认设置成 Debug 形式
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CXX_FLAGS
    -g
    -Wall
    -std=c++11
    -D_PTHREADS
    -Wno-unused-parameter
)


set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

# 分号替换成空格，将 CXX_FLAGS 变量的值 ${CXX_FLAGS} 赋给 CMAKE_CXX_FLAGS 变量
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

# 字符转成大写，这里将 Debug 转成了 DEBUG
string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)

# message 用于向终端输出用户定义的信息
# SATUS，输出前缀为 — 的信息
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

# 添加 WebServer 子目录
add_subdirectory(WebServer)