cmake_minimum_required(VERSION 3.6)
project(Queue)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES
    catch.hpp
    Queue.cpp
    Queue.h
    Node.h
    Flags.h
    tests.cpp)

add_executable(Queue ${SOURCE_FILES})
target_link_libraries(Queue ${CMAKE_SOURCE_DIR}/libQueue_${CMAKE_SYSTEM_NAME}.a)
set_target_properties(Queue PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR} )
