//
// Created by chaku on 10/12/24.
//

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <ranges>

#include "day05.hpp"

auto test() -> int {
    std::string test_input = R"(47|53
97|13
97|61
97|47
75|29
61|13
75|53
29|13
97|29
53|29
61|53
97|53
61|29
47|13
75|47
97|75
47|61
75|61
47|29
75|13
53|13

75,47,61,53,29
97,61,53,29,13
75,29,13
75,97,47,61,53
61,13,29
97,13,75,29,47)";

    assert(aoc::day05::sum_of_correctly_ordered_middle_pages(test_input) == 143);
    assert(aoc::day05::sum_of_fixed_incorrectly_ordered_middle_pages(test_input) == 123);
    return 0;
}

auto parse_and_run(std::string_view path) -> int {
    std::vector<std::string> data;
    std::fstream file(static_cast<std::string>(path));
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(path) << "\n";
        return 1;
    }
    std::string input;
    std::string line;
    while(std::getline(file, line)) {
        line.append("\n");
        input += line;

    }
    std::cout << "Part 1 solution : " << aoc::day05::sum_of_correctly_ordered_middle_pages(input) << "\n";
    //std::cout << "Part 2 solution : " << aoc::day04::get_x_mas_count(input) << "\n";
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

