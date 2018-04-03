
cmake_minimum_required(VERSION 3.6)
project(Luchthaven)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES main.cpp tinystr.cpp tinystr.h tinyxml.cpp tinyxml.h tinyxmlerror.cpp Airportsim.cpp Airportsim.h Runway.cpp Runway.h Airplane.cpp Airplane.h Airport.cpp Airport.h tinyxmlparser.cpp DesignByContract.h output_system.cpp output_system.h AirportsimImporter.cpp AirportsimImporter.h ImportTest.cpp AirportUtils.h AirportUtils.cpp)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES test.cpp tinystr.cpp tinystr.h tinyxml.cpp tinyxml.h tinyxmlerror.cpp Airportsim.cpp Airportsim.h Runway.cpp Runway.h Airplane.cpp Airplane.h Airport.cpp Airport.h tinyxmlparser.cpp DesignByContract.h output_system.cpp output_system.h AirportUtils.h AirportUtils.cpp)

# Create RELEASE target
add_executable(Airport_simulator ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(Airport_simulator_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(Airport_simulator_debug gtest)