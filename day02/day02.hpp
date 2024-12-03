//
// Created by chaku on 02/12/24.
//

#ifndef AOC2024_DAY02_HPP
#define AOC2024_DAY02_HPP

#include <vector>
#include <array>
#include <cstdint>
#include <algorithm>
#include <ranges>

namespace aoc::day02 {
    auto safe_report_count(std::vector<std::vector<int>>& input) -> uint64_t {
        auto check = [](const std::vector<int>& input_range, int lower_bound_inclusive, int upper_bound_inclusive) {
            return std::ranges::all_of(input_range | std::views::pairwise, [&](const auto& pair) {
                const auto& [fst, snd] = pair;
                auto result = fst - snd;
                return lower_bound_inclusive <= result && result <= upper_bound_inclusive;
            });
        };
        uint64_t result{0};
        std::for_each(input.begin(), input.end(), [&check, &result](const std::vector<int>& input_range) {
            if (check(input_range, 1, 3) || check(input_range, -3, -1)) {
                result++;
            }
        });
        return result;
    }

}
#endif //AOC2024_DAY02_HPP
