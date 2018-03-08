cmake_minimum_required(VERSION 3.6)
project(Luchthaven)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp tinystr.cpp tinystr.h tinyxml.cpp tinyxml.h tinyxmlerror.cpp)
add_executable(Luchthaven ${SOURCE_FILES})