//
// Created by chaku on 22/12/24.
//

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>

#include "day09.hpp"

auto test() -> int {
    const std::string test_input{ "2333133121414131402"};
    assert(aoc::day09::get_checksum(test_input) == 1928);
    assert(aoc::day09::get_checksum(test_input, true) == 2858);
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
    std::cout << "Part 1 solution : " << aoc::day09::get_checksum(line) << "\n";
    std::cout << "Part 2 solution : " << aoc::day09::get_checksum(line, true) << "\n";
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

