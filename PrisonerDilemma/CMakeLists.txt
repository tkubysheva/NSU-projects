cmake_minimum_required(VERSION 3.15.3)
project(PrisonerDilemma)

set(CMAKE_CXX_STANDARD 14)

#-------------------- Create a library -----------------------------------------
#Generate the shared library from the library sources
#-------------------------------------------------------------------------------
add_library(${PROJECT_NAME}_rand SHARED
        strategies/random.cpp
        )
add_library(${PROJECT_NAME}_alld SHARED
        strategies/all-defect.cpp
        )
add_library(${PROJECT_NAME}_chch SHARED
        strategies/change-choice.cpp
        )
add_library(${PROJECT_NAME}_forgrev SHARED
        strategies/forgive-revenge.cpp
        )
add_library(${PROJECT_NAME}_ptf SHARED
        strategies/poor-trusting-fool.cpp
        )
add_library(${PROJECT_NAME}_stft SHARED
        strategies/soft-tit-for-tat.cpp
        )
add_library(${PROJECT_NAME}_ttft SHARED
        strategies/tough-tit-for-tat.cpp
        )

add_library(${PROJECT_NAME}_rand::random ALIAS ${PROJECT_NAME}_rand)
add_library(${PROJECT_NAME}_alld::all-defect ALIAS ${PROJECT_NAME}_alld)
add_library(${PROJECT_NAME}_chch::change-choice ALIAS ${PROJECT_NAME}_chch)
add_library(${PROJECT_NAME}_forgrev::forgive-revenge ALIAS ${PROJECT_NAME}_forgrev)
add_library(${PROJECT_NAME}_ptf::poor-trusting-fool ALIAS ${PROJECT_NAME}_ptf)
add_library(${PROJECT_NAME}_stft::soft-tit-for-tat ALIAS ${PROJECT_NAME}_stft)
add_library(${PROJECT_NAME}_ttft::tough-tit-for-tat ALIAS ${PROJECT_NAME}_ttft)

target_include_directories(${PROJECT_NAME}_rand
        PUBLIC
        ${PROJECT_SOURCE_DIR}/strategies
        )
target_include_directories(${PROJECT_NAME}_alld
        PUBLIC
        ${PROJECT_SOURCE_DIR}/strategies
        )
target_include_directories(${PROJECT_NAME}_chch
        PUBLIC
        ${PROJECT_SOURCE_DIR}/strategies
        )
target_include_directories(${PROJECT_NAME}_forgrev
        PUBLIC
        ${PROJECT_SOURCE_DIR}/strategies
        )
target_include_directories(${PROJECT_NAME}_ptf
        PUBLIC
        ${PROJECT_SOURCE_DIR}/strategies
        )
target_include_directories(${PROJECT_NAME}_stft
        PUBLIC
        ${PROJECT_SOURCE_DIR}/strategies
        )
target_include_directories(${PROJECT_NAME}_ttft
        PUBLIC
        ${PROJECT_SOURCE_DIR}/strategies
        )
#------------------- Create an executable --------------------------------------
file(GLOB
        CPP_SOURCES "*.cpp")
file(GLOB
        H_SOURCES "*.h")

add_executable(${PROJECT_NAME} ${CPP_SOURCES} ${H_SOURCES})

# link the new library target with the binary target
target_link_libraries( ${PROJECT_NAME}
        PRIVATE
        ${PROJECT_NAME}_rand::random
        )
target_link_libraries( ${PROJECT_NAME}
        PRIVATE
        ${PROJECT_NAME}_rand::random
        )
target_link_libraries( ${PROJECT_NAME}
        PRIVATE
        ${PROJECT_NAME}_alld::all-defect
        )
target_link_libraries( ${PROJECT_NAME}
        PRIVATE
        ${PROJECT_NAME}_chch::change-choice
        )
target_link_libraries( ${PROJECT_NAME}
        PRIVATE
        ${PROJECT_NAME}_forgrev::forgive-revenge
        )
target_link_libraries( ${PROJECT_NAME}
        PRIVATE
        ${PROJECT_NAME}_ptf::poor-trusting-fool
        )
target_link_libraries( ${PROJECT_NAME}
        PRIVATE
        ${PROJECT_NAME}_stft::soft-tit-for-tat
        )
target_link_libraries( ${PROJECT_NAME}
        PRIVATE
        ${PROJECT_NAME}_ttft::tough-tit-for-tat
        )


ADD_SUBDIRECTORY (googletest)
include_directories(googletest/googletest/include)

target_link_libraries(gtest gtest_main)