//
// Created by chaku on 07/12/24.
//

#ifndef AOC2024_DAY03_HPP
#define AOC2024_DAY03_HPP

#include <regex>
#include <string>
#include <stack>
#include <ranges>

namespace aoc::day03 {
    static const std::regex mul_expression(R"(mul\((\d{1,3}),(\d{1,3})\))");

    auto fill_positions = [](const std::string& sequence, const std::string& subsequence)-> std::stack<size_t> {
        std::vector<size_t> positions_vec;
        auto pos = sequence.find(subsequence);
        while(pos != std::string::npos) {
            positions_vec.emplace_back(pos);
            pos = sequence.find(subsequence, pos + subsequence.length());
        }
        std::sort(positions_vec.begin(), positions_vec.end(), std::greater<>());
        std::stack<size_t> positions(positions_vec.begin(), positions_vec.end());
        return positions;
    };

    auto add_all_multiplications(const std::vector<std::string>& input) -> uint64_t {
        uint64_t result{0};
        for (const auto& sequence : input) {
            auto matches_begin = std::sregex_iterator(sequence.begin(), sequence.end(), mul_expression);
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

    auto add_all_multiplications_if_enabled(const std::vector<std::string>& input) -> uint64_t {
        const std::string do_expr{"do()"};
        const std::string dont_expr{"don't()"};

        uint64_t result{0};
        std::string full;
        for (const auto& section : input) {
            full.append(section);
        }

        auto do_stack = fill_positions(full, do_expr);
        do_stack.push(0);

        while(!do_stack.empty()) {
            auto do_start = do_stack.top();
            do_stack.pop();
            auto dont_start = full.find(dont_expr, do_start);
            while(!do_stack.empty() && dont_start > do_stack.top()) {
                do_stack.pop();
            }
            auto enabled = full.substr(do_start, dont_start - do_start);
            auto matches_begin = std::sregex_iterator(enabled.begin(), enabled.end(), mul_expression);
            for (std::sregex_iterator j = matches_begin; j != std::sregex_iterator(); ++j) {
                std::smatch match = *j;
                const int fst = std::stoi(match[1].str());
                const int snd = std::stoi(match[2].str());
                result += fst * snd;
            }
        }
        return result;
    }
}

#endif //AOC2024_DAY03_HPP
