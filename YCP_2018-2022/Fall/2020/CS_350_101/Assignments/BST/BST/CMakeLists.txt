cmake_minimum_required(VERSION 3.6)
project(BST)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES
    catch.hpp
    BST.cpp
    BST.h
    Node.h
    Flags.h
    PrettyPrinter.h
    PrettyPrinter.cpp
    tests.cpp)

add_executable(BST ${SOURCE_FILES})
target_link_libraries(BST ${CMAKE_SOURCE_DIR}/libBST_${CMAKE_SYSTEM_NAME}.a)
set_target_properties(BST PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR} )
