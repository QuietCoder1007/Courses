cmake_minimum_required(VERSION 3.16)   # CMake version check
project(insertionSorter)               
set(CMAKE_CXX_STANDARD 11)             # Enable c++11 standard
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#Main
set(SOURCE_FILES insertionSorter.cpp)
add_executable(insertionSorter ${SOURCE_FILES})


