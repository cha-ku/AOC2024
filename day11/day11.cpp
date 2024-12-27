//
// Created by chaku on 26/12/24.
//

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>

#include "day11.hpp"

auto test() -> int {
    const std::string test_input1{"125 17"};
    assert(aoc::day11::num_stones_after_blinks(test_input1, 25) == 55312);
    return 0;
}

auto parse_and_run(std::string_view path) -> int {
    std::vector<std::string> data;
    std::fstream file(static_cast<std::string>(path));
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(path) << "\n";
        return 1;
    }
    std::string line;
    std::getline(file, line);
    std::cout << "Part 1 solution : " << aoc::day11::num_stones_after_blinks(line, 25) << "\n";
    std::cout << "Part 2 solution : " << aoc::day11::num_stones_after_blinks_part2(line, 75) << "\n";
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