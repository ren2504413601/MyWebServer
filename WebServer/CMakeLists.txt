# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

set (EXTRA_LIBS ${EXTRA_LIBS} pthread)

# 指定生成目标
add_executable(main ${DIR_SRCS})
target_link_libraries (main  ${EXTRA_LIBS})

add_subdirectory(test)
