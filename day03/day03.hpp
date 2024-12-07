//
// Created by chaku on 07/12/24.
//

#ifndef AOC2024_DAY03_HPP
#define AOC2024_DAY03_HPP

#include <regex>
#include <string>

namespace aoc::day03 {
    auto add_all_multiplications(const std::vector<std::string>& input) -> uint64_t {
        uint64_t result{0};
        std::regex expression("mul\\((\\d{1,3}),(\\d{1,3})\\)");
        for (const auto& sequence : input) {
            auto matches_begin = std::sregex_iterator(sequence.begin(), sequence.end(), expression);
            auto matches_end = std::sregex_iterator();
            for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
                const std::smatch& match = *i;
                const int fst = std::stoi(match[1].str());
                const int snd = std::stoi(match[2].str());
                result += fst * snd;
            }
        }
        return result;
    }
}

#endif //AOC2024_DAY03_HPP
