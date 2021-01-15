cmake_minimum_required(VERSION 3.15.3)
project(PrisonerDilemma)

set(CMAKE_CXX_STANDARD 20)



#------------------- Create an executable --------------------------------------
file(GLOB
        CPP_SOURCES "*.cpp")
file(GLOB
        H_SOURCES "*.h")

add_executable(${PROJECT_NAME} ${CPP_SOURCES} ${H_SOURCES} tests.cpp)

#
ADD_SUBDIRECTORY (googletest)
include_directories(googletest/googletest/include)

target_link_libraries(${PROJECT_NAME} gtest gtest_main)