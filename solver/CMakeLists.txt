cmake_minimum_required(VERSION 4.1)
project(solver)

set(CMAKE_CXX_STANDARD 23)

add_executable(solver main.cpp
        calculations.cpp
        calculations.h)
