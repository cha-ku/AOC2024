//
// Created by chaku on 01/12/24.
//

#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_map>

namespace aoc::day01 {
    auto convert (std::vector<std::string> &string_data) -> std::vector<uint64_t> {
        auto int_data = string_data
                        | std::views::transform([](const std::string& s) { return std::stoul(s); })
                        | std::ranges::to<std::vector>();
        return int_data;
    };
    auto total_distance(std::vector<std::string> &raw_data_left, std::vector<std::string> &raw_data_right) -> uint64_t {
        std::vector<uint64_t> left{convert(raw_data_left)};
        std::sort(left.begin(), left.end());
        std::vector<uint64_t> right{convert(raw_data_right)};
        std::sort(right.begin(), right.end());
        auto abs_sum = std::ranges::views::zip_transform([](const auto left_val, const auto right_val) {
            return left_val > right_val ? left_val - right_val : right_val - left_val;
        }, left, right);
        return std::reduce(abs_sum.cbegin(), abs_sum.cend(), 0ul);
    }

    auto similarity_score(std::vector<std::string> &raw_data_left, std::vector<std::string> &raw_data_right) -> uint64_t {
        std::vector<uint64_t> left{convert(raw_data_left)};
        std::vector<uint64_t> right{convert(raw_data_right)};
        std::unordered_map<uint64_t, uint64_t> r_counts;
        std::for_each(right.cbegin(), right.cend(), [&r_counts](const uint64_t& r) {
            r_counts[r]++;
        });
        uint64_t result{0};
        std::for_each(left.cbegin(), left.cend(), [&r_counts, &result](const uint64_t& l) mutable {
            if (r_counts.contains(l)) {
                result += l * r_counts[l];
            }
        });
        return result;
    }
}
