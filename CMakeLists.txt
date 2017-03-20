cmake_minimum_required(VERSION 3.6)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES time1.cpp time1.h application.cpp application.h time2.cpp time2.h)
add_executable(Project1 ${SOURCE_FILES})