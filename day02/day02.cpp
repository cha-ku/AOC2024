//
// Created by chaku on 02/12/24.
//

#include <array>
#include <cassert>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "day02.hpp"

int test() {
    std::vector<std::vector<int>> test_input{
        {7, 6, 4, 2, 1},
        {1, 2, 7, 8, 9},
        {9, 7, 6, 2, 1},
        {1, 3, 2, 4, 5},
        {8, 6, 4, 4, 1},
        {1, 3, 6, 7, 9}
    };
    assert(aoc::day02::safe_report_count(test_input) == 2);
    return 0;
}

int parse_and_run(std::string_view path) {
    std::vector<std::string> data;
    std::fstream file(static_cast<std::string>(path));
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(path) << "\n";
        return 1;
    }
    using std::operator""sv;
    constexpr auto delim{" "sv};
    std::vector<std::vector<int>> input;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> nums;
        for(auto num : line | std::views::split(delim)) {
            nums.emplace_back(std::stoi(std::string(num.begin(), num.end())));
        }
        input.emplace_back(nums);
    }
    std::cout << "Part 1 solution : " << aoc::day02::safe_report_count(input) << "\n";
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
