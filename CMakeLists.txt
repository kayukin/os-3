cmake_minimum_required(VERSION 3.3)
project(os_3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp MyUNIXLib.cpp MyUNIXLib.h)
add_executable(os_3 ${SOURCE_FILES})