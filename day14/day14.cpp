//
// Created by chaku on 31/12/24.
//

#include <cassert>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "day14.hpp"

auto test() -> int {
    std::vector<std::string> test_input1{
            "p=0,4 v=3,-3",
            "p=6,3 v=-1,-3",
            "p=10,3 v=-1,2",
            "p=2,0 v=2,-1",
            "p=0,0 v=1,3",
            "p=3,0 v=-2,-2",
            "p=7,6 v=-1,-3",
            "p=3,0 v=-1,-2",
            "p=9,3 v=2,3",
            "p=7,3 v=-1,2",
            "p=2,4 v=2,-3",
            "p=9,5 v=-3,-3"
    };
    assert(aoc::day14::get_safety_factor(test_input1, 7, 11, 100) == 12);
    //std::cout << aoc::day14::check_easter_egg(test_input1, 7, 11) << "\n";
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
    std::cout << "Part 1 solution : " << aoc::day14::get_safety_factor(input, 103, 101, 100) << "\n";
    std::cout << "Part 2 solution : " << aoc::day14::check_easter_egg(input, 103, 101) << "\n";
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
