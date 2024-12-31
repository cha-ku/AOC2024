//
// Created by chaku on 29/12/24.
//

#include <cassert>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "day13.hpp"


auto test() -> int {
    std::vector<std::string> test_input1{
            "Button A: X+94, Y+34",
            "Button B: X+22, Y+67",
            "Prize: X=8400, Y=5400",
            "Button A: X+26, Y+66",
            "Button B: X+67, Y+21",
            "Prize: X=12748, Y=12176",
            "Button A: X+17, Y+86",
            "Button B: X+84, Y+37",
            "Prize: X=7870, Y=6450",
            "Button A: X+69, Y+23",
            "Button B: X+27, Y+71",
            "Prize: X=18641, Y=10279"
    };
    assert(aoc::day13::get_min_tokens(test_input1) == 480);
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
        if (line.empty()) {
            continue;
        }
        input.emplace_back(line);
    }
    std::cout << "Part 1 solution : " << aoc::day13::get_min_tokens(input) << "\n";
    std::cout << "Part 2 solution : " << aoc::day13::get_min_tokens(input, true) << "\n";
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
