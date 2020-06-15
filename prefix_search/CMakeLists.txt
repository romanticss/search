cmake_minimum_required(VERSION 3.15)
project(prefix_search)
set(CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(library)
add_executable(prefix_search main.cpp)
#添加链接库
target_link_libraries(prefix_search struct)
