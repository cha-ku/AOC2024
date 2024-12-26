//
// Created by chaku on 25/12/24.
//

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>

#include "day10.hpp"

auto test() -> int {
    const std::vector<std::string> test_input1 = {
            "...0...",
            "...1...",
            "...2...",
            "6543456",
            "7.....7",
            "8.....8",
            "9.....9"
    };
    //std::cout << aoc::day10::sum_of_trailheads(test_input1) << "\n";
    assert(aoc::day10::sum_of_trailheads(test_input1) == 2);

    const std::vector<std::string> test_input2 = {
            "..90..9",
            "...1.98",
            "...2..7",
            "6543456",
            "765.987",
            "876....",
            "987...."
    };
    assert(aoc::day10::sum_of_trailheads(test_input2) == 4);

    const std::vector<std::string> test_input3 = {
            "10..9..",
            "2...8..",
            "3...7..",
            "4567654",
            "...8..3",
            "...9..2",
            ".....01"
    };
    assert(aoc::day10::sum_of_trailheads(test_input3) == 3);

    const std::vector<std::string> test_input4 = {
            "89010123",
            "78121874",
            "87430965",
            "96549874",
            "45678903",
            "32019012",
            "01329801",
            "10456732"
    };
    assert(aoc::day10::sum_of_trailheads(test_input4) == 36);

    const std::vector<std::string> test_input5 = {
            ".....0.",
            "..4321.",
            "..5..2.",
            "..6543.",
            "..7..4.",
            "..8765.",
            "..9...."
    };
    assert(aoc::day10::sum_of_ratings(test_input5) == 3);

    const std::vector<std::string> test_input6 = {
            "..90..9",
            "...1.98",
            "...2..7",
            "6543456",
            "765.987",
            "876....",
            "987...."
    };
    assert(aoc::day10::sum_of_ratings(test_input6) == 13);

    const std::vector<std::string> test_input7 = {
            "012345",
            "123456",
            "234567",
            "345678",
            "4.6789",
            "56789."
    };
    assert(aoc::day10::sum_of_ratings(test_input7) == 227);

    const std::vector<std::string> test_input8 = {
            "89010123",
            "78121874",
            "87430965",
            "96549874",
            "45678903",
            "32019012",
            "01329801",
            "10456732"
    };
    assert(aoc::day10::sum_of_ratings(test_input8) == 81);

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
    std::cout << "Part 1 solution : " << aoc::day10::sum_of_trailheads(input) << "\n";
    std::cout << "Part 2 solution : " << aoc::day10::sum_of_ratings(input) << "\n";
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
