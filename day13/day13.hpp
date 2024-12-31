//
// Created by chaku on 29/12/24.
//

#ifndef AOC2024_DAY13_HPP
#define AOC2024_DAY13_HPP

#include <cmath>
#include <vector>
#include <ranges>
#include <regex>

namespace aoc::day13 {
    auto get_min_tokens(const std::vector<std::string>& input, const bool part2=false) -> uint64_t {
        uint64_t result{0};
        static const std::regex num_regex(R"(\d+)");
        for (const auto& group : input | std::views::chunk(3)) {
            // Button A
            std::vector<long double> coefficients_A;
            // Button B
            std::vector<long double> coefficients_B;
            // Prize
            std::vector<long double> prize;
            for (const auto &[idx, line]: std::views::enumerate(group)) {
                for (std::sregex_iterator itr = std::sregex_iterator(line.begin(), line.end(), num_regex);
                     itr != std::sregex_iterator(); ++itr) {
                    const std::smatch &match = *itr;
                    auto num = std::stold(match[0].str());
                    // Button A
                    if (idx == 0) {
                        coefficients_A.emplace_back(num);
                        continue;
                    }
                    // Button B
                    if (idx == 1) {
                        coefficients_B.emplace_back(num);
                        continue;
                    }
                    // Prize
                    if (idx == 2) {
                        if (!part2) {
                            prize.emplace_back(num);
                        }
                        else {
                            prize.emplace_back(10000000000000 + num);
                        }
                        continue;
                    }
                }
            }
            if ((coefficients_B[1] * coefficients_A[0] - coefficients_B[0] * coefficients_A[1]) != 0 &&
                (coefficients_A[1] * coefficients_B[0] - coefficients_A[0] * coefficients_B[1]) != 0) {
                long double a = (coefficients_B[1] * prize[0] - coefficients_B[0] * prize[1]) / (coefficients_B[1] * coefficients_A[0] - coefficients_B[0] * coefficients_A[1]);
                long double b = (coefficients_A[1] * prize[0] - coefficients_A[0] * prize[1]) / (coefficients_A[1] * coefficients_B[0] - coefficients_A[0] * coefficients_B[1]);
                // check if a % 1 == 0 (i.e. if a is an int)
                if (std::ceil(a) == a && std::ceil(b) == b) {
                    result += 3*static_cast<uint64_t>(a) + static_cast<uint64_t>(b);
                }
            }
        }
        return result;
    }
}

#endif //AOC2024_DAY13_HPP
