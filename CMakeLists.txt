cmake_minimum_required(VERSION 3.26)
project(AOC2024)
find_package(ctre CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

add_compile_options(-Wall -Werror -Wpedantic -Wno-sign-compare)

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

add_executable(day10
        day10/day10.cpp
        day10/day10.hpp)

add_executable(day11
        day11/day11.cpp
        day11/day11.hpp)

add_executable(day12
        day12/day12.cpp
        day12/day12.hpp)

add_executable(day13
        day13/day13.cpp
        day13/day13.hpp)

add_executable(day14
        day14/day14.cpp
        day14/day14.hpp)
target_link_libraries(day14 PRIVATE ctre::ctre)
