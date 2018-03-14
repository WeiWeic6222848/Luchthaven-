cmake_minimum_required(VERSION 3.6)
project(Luchthaven)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp tinystr.cpp tinystr.h tinyxml.cpp tinyxml.h tinyxmlerror.cpp Airportsim.cpp Airportsim.h Runway.cpp Runway.h Airplane.cpp Airplane.h Airport.cpp Airport.h tinyxmlparser.cpp)
add_executable(Luchthaven ${SOURCE_FILES})