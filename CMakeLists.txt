cmake_minimum_required(VERSION 3.15)
project(327_project2_starter)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(327_project2_starter
        src/array_functions.cpp
        src/array_functions.h
        src/constants.h
        src/Project2.cpp
        src/utilities.cpp
        src/utilities.h)
