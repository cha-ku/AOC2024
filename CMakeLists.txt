cmake_minimum_required(VERSION 3.26)
project(AOC2024)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

add_executable(day01
        day01/day01.hpp
        day01/day01.cpp)

add_executable(day02
        day02/day02.cpp
        day02/day02.hpp)


add_executable(day03
        day03/day03.cpp
        day03/day03.hpp)
