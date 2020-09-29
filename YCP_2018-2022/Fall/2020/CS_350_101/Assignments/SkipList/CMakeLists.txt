cmake_minimum_required(VERSION 3.6)
project(SkipList)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES
    catch.hpp
    SkipList.cpp
    SkipList.h
    Node.h
    Flags.h
    tests.cpp)

add_executable(SkipList ${SOURCE_FILES})
target_link_libraries(SkipList ${CMAKE_SOURCE_DIR}/libSkipList_${CMAKE_SYSTEM_NAME}.a)
set_target_properties(SkipList PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR} )
