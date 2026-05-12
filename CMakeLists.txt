cmake_minimum_required(VERSION 4.1)
project(mownit)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffp-contract=off -O0 -fno-fast-math -fno-unsafe-math-optimizations")
add_executable(mownit
        lab1/float/main.cpp
)
add_executable(new_target lab1/dobule/main.cpp)
add_executable(long lab1/long_double/main.cpp)
