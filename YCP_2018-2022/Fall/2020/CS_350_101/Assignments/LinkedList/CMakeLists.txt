cmake_minimum_required(VERSION 3.6)
project(LinkedList)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES
    catch.hpp
    LinkedList.cpp
    LinkedList.h
    Node.h
    Flags.h
    tests.cpp)

add_executable(LinkedList ${SOURCE_FILES})
target_link_libraries(LinkedList ${CMAKE_SOURCE_DIR}/libLinkedList_${CMAKE_SYSTEM_NAME}.a)
set_target_properties(LinkedList PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR} )
