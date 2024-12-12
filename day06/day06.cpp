//
// Created by chaku on 11/12/24.
//

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <ranges>

#include "day06.hpp"

auto test() -> int {
    std::vector<std::string> test_input{
        "....#.....",
        ".........#",
        "..........",
        "..#.......",
        ".......#..",
        "..........",
        ".#..^.....",
        "........#.",
        "#.........",
        "......#..."
    };
    assert(aoc::day06::get_unique_positions(test_input) == 41);
    return 0;
}

auto parse_and_run(std::string_view path) -> int {
    std::vector<std::string> data;
    std::fstream file(static_cast<std::string>(path));
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(path) << "\n";
        return 1;
    }
    std::vector<std::string> input;
    std::string line;
    while(std::getline(file, line)) {
        input.emplace_back(line);
    }
    std::cout << "Part 1 solution : " << aoc::day06::get_unique_positions(input) << "\n";
//    std::cout << "Part 2 solution : " << aoc::day05::sum_of_fixed_incorrectly_ordered_middle_pages(input) << "\n";
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        return test();
    }
    else if (argc == 2) {
        return parse_and_run(argv[1]);
    }
    return 0;
}

