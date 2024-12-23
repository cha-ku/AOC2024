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

add_executable(day04
        day04/day04.cpp
        day04/day04.hpp)

add_executable(day05
        day05/day05.cpp
        day05/day05.hpp)

add_executable(day06
        day06/day06.cpp
        day06/day06.hpp)

add_executable(day07
        day07/day07.cpp
        day07/day07.hpp)

add_executable(day08
        day08/day08.cpp
        day08/day08.hpp)

add_executable(day09
        day09/day09.cpp
        day09/day09.hpp)
