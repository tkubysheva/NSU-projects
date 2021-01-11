cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
project(hash_table)
add_executable(hash_table table.cpp table.h tests.cpp)

ADD_SUBDIRECTORY (googletest)
include_directories(googletest/googletest/include)

target_link_libraries(hash_table gtest gtest_main)