cmake_minimum_required(VERSION 3.12)
project(not_primary)

set(CMAKE_CXX_STANDARD 14)

FILE(GLOB SRCFILES *.cpp)

FIND_PACKAGE(OpenMP REQUIRED)
if (OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    include_directories("/opt/intel/mkl/include")
endif ()

include_directories(.)

add_executable(not_primary main.cpp ${SRCFILES})
