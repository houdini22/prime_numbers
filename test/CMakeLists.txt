cmake_minimum_required(VERSION 3.12)
project(test)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -m64 -flto -march=native -funroll-loops -mavx -msse4.2 -fopenmp")

add_executable(test main.cpp)