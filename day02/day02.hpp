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
#include <numeric>

namespace aoc::day02 {
    auto print = [](const auto& container) {
        std::for_each(container.cbegin(), container.cend(), [](const auto& elem) {
            std::cout << elem << " ";
        });
        std::cout << "\n";
    };
    auto is_safe = [](const std::vector<int>& input_range, int lower_bound_inclusive, int upper_bound_inclusive) -> bool {
        return std::ranges::all_of(input_range | std::views::pairwise, [&](const auto& pair) {
            const auto& [fst, snd] = pair;
            auto result = fst - snd;
            return lower_bound_inclusive <= result && result <= upper_bound_inclusive;
        });
    };

    auto safe_count = [](std::vector<std::vector<int>>& input) -> uint64_t {
        uint64_t result{0};
        std::for_each(input.begin(), input.end(), [&](const std::vector<int>& input_range) {
            if (is_safe(input_range, 1, 3) || is_safe(input_range, -3, -1)) {
                result++;
            }
        });
        return result;
    };

    auto safe_with_tolerance_count = [](std::vector<std::vector<int>>& input) -> uint64_t {
        uint64_t result{0};
        for(const auto& levels: input) {
            if (is_safe(levels, 1, 3) || is_safe(levels, -3, -1)) {
                result++;
                continue;
            }
            constexpr uint64_t start_index{0};
            for (const auto& index : std::views::iota(start_index, static_cast<uint64_t>(levels.size()))) {
                auto vec_level = levels;
                vec_level.erase(vec_level.begin() + index);
                if (is_safe(vec_level, 1, 3) || is_safe(vec_level, -3, -1)) {
                    result++;
                    break;
                }
            }
        }
        return result;
    };
}
#endif //AOC2024_DAY02_HPP
