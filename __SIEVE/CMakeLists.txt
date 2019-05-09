cmake_minimum_required(VERSION 3.12)
project(not_primary)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(not_primary
        bigInt.cpp
        bigInt.h
        main.cpp)
