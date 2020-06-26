cmake_minimum_required(VERSION 3.15)
project(invert_search)
set(CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(library)
include_directories(./3rdparty/include/)
add_executable(invert_search main.cpp)
#添加链接库
target_link_libraries(invert_search struct)
