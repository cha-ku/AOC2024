cmake_minimum_required(VERSION 3.30)
project(AOC2024)

set(CMAKE_CXX_STANDARD 23)

add_executable(day01)

target_sources(day01 PUBLIC
        day01/day01.cpp)