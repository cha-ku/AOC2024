#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <iomanip>

#include "day01.hpp"

int test() {
    std::vector<std::string> left_list{"3", "4", "2", "1", "3", "3"};
    std::vector<std::string> right_list{"4", "3", "5", "3", "9", "3"};
    assert(aoc::day01::total_distance(left_list, right_list) == 11);
    assert(aoc::day01::similarity_score(left_list, right_list) == 31);
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
    constexpr auto delim{"   "sv};
    std::vector<std::string> left_list;
    std::vector<std::string> right_list;
    std::string line;
    while (std::getline(file, line)) {
        auto parts  = line | std::views::split(delim) | std::views::transform([](auto&& word) {
            return std::string(word.begin(), word.end());
        });
        // TODO: this was copied over from ChatGPT this makes no sense replace this ChatGPT code with something sensible
        auto it = parts.begin();
        if (it != parts.end()) {
            left_list.emplace_back(*it++);
        }
        if (it != parts.end()) {
            right_list.emplace_back(*it);
        }
    }
    std::cout << "Part 1 solution : " << aoc::day01::total_distance(left_list, right_list) << "\n";
    std::cout << "Part 2 solution :  " << aoc::day01::similarity_score(left_list, right_list) << "\n";
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
