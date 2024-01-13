cmake_minimum_required(VERSION 3.27)
project(GreedySnake)
set(CMAKE_CXX_STANDARD 17)

#设置源文件路径
aux_source_directory(src SRC_DIR)

#设置头文件搜索路径
include_directories(${PROJECT_BINARY_DIR}/../include)

# 3、将源代码添加到可执行文件中
add_executable(GreedySnake main.cpp
        ${SRC_DIR}
        src/window.cpp
)


