//
// Created by chaku on 21/12/24.
//

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>

#include "day08.hpp"

auto test() -> int {
    const std::vector<std::string> test_input{
            "............",
            "........0...",
            ".....0......",
            ".......0....",
            "....0.......",
            "......A.....",
            "............",
            "............",
            "........A...",
            ".........A..",
            "............",
            "............"
    };
    assert(aoc::day08::get_num_unique_locations(test_input) == 14);
    assert(aoc::day08::get_num_unique_locations(test_input, false) == 34);
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
    std::cout << "Part 1 solution : " << aoc::day08::get_num_unique_locations(input) << "\n";
    std::cout << "Part 2 solution : " << aoc::day08::get_num_unique_locations(input, false) << "\n";
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

