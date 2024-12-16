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

#include "day07.hpp"

auto test() -> int {
    const std::vector<std::string> test_input{
            "190: 10 19",
            "3267: 81 40 27",
            "83: 17 5",
            "156: 15 6",
            "7290: 6 8 6 15",
            "161011: 16 10 13",
            "192: 17 8 14",
            "21037: 9 7 18 13",
            "292: 11 6 16 20"
    };
    assert(aoc::day07::calibration_result_if_true(test_input) == 3749);
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
    std::cout << "Part 1 solution : " << aoc::day07::calibration_result_if_true(input) << "\n";
//    std::cout << "Part 2 solution : " << aoc::day07::get_num_possible_obstruction_locations(input) << "\n";
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

