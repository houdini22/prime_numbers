cmake_minimum_required(VERSION 3.12)
project(sieve)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(sieve
        bigInt.cpp
        bigInt.h
        main.cpp)
