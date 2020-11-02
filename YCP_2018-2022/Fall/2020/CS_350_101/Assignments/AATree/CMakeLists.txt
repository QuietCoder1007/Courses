cmake_minimum_required(VERSION 3.6)
project(AATree)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES
    Flags.h
    Node.h
    AATree.h
    AATree.cpp
    AATreePrettyPrinter.h
    AATreePrettyPrinter.cpp
    catch.hpp
    tests.cpp)

add_executable(AATree ${SOURCE_FILES})
target_link_libraries(AATree ${CMAKE_SOURCE_DIR}/libAATree_${CMAKE_SYSTEM_NAME}.a)
set_target_properties(AATree PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR} )
