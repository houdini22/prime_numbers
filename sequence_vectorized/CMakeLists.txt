cmake_minimum_required(VERSION 3.12)
project(sequence_vectorized)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(sequence_vectorized
        bigInt.h
        main.cpp)
