//
// Created by chaku on 26/12/24.
//

#ifndef AOC2024_DAY11_HPP
#define AOC2024_DAY11_HPP

#include <vector>
#include <string>
#include <ranges>
#include <unordered_map>


namespace aoc::day11 {

    using std::operator""sv;
    auto num_stones_after_blinks(const std::string& input, const uint64_t num_blinks) -> uint64_t {
        std::string input_copy = input;
        for ([[maybe_unused]] const auto index : std::views::iota(0) | std::views::take(num_blinks)) {
            std::string result;
            for (const auto num : input_copy | std::views::split(" "sv)) {
                std::string num_str{num.begin(), num.end()};
                if (num_str.empty()) {
                    continue;
                }
                if (num_str == "0") {
                    result += "1 ";
                    continue;
                }
                if (num_str.size() % 2 == 0) {
                    result += std::string(num_str.begin(), num_str.begin()+(num_str.size()/2)) + " ";
                    const auto& second_half = std::string(num_str.begin() + (num_str.size()/2), num_str.end());
                    const auto second_half_num = std::stoull(second_half);
                    const auto& second_half_fixed = std::to_string(second_half_num);
                    result += second_half_fixed + " ";
                    continue;
                }
                result += std::to_string(std::stoull(num_str) * 2024) + " ";
            }
            //std::cout << index << " : " << result << "\n";
            input_copy = result;
        }
        uint64_t result{0};
        for (const auto num : input_copy | std::views::split(" "sv)) {
            std::string num_str{num.begin(), num.end()};
            if (num_str.empty()) {
                continue;
            }
            result++;
        }
        return result;
    }

    // Simulation with part 1 took forever to run
    // couldn't have implemented this without https://www.reddit.com/r/adventofcode/comments/1hbm0al/2024_day_11_solutions/m290nvp/
    // https://github.com/helenzhangyc/aoc2024/blob/main/Day%2011%20Plutonian%20Pebbles/d11p2.cpp
    using ui64 = uint64_t;
    auto num_stones_after_blinks_part2(const std::string& input, const uint64_t num_blinks) -> uint64_t {
        std::unordered_map<ui64, ui64> stone_counts;
        for (const auto num : input | std::views::split(" "sv)) {
            stone_counts[std::stoull(std::string(num.begin(), num.end()))] = 1;
        }
        for ([[maybe_unused]] auto index : std::views::iota(0) | std::views::take(num_blinks)) {
            std::unordered_map<ui64, ui64> tmp;
            for (const auto& [key, count] : stone_counts) {
                if (key == 0) {
                    tmp[1] += count;
                }
                else if (const auto key_str = std::to_string(key); key_str.size() % 2 == 0) {
                    const auto& first_half = std::stoull(std::string(key_str.begin(), key_str.begin()+(key_str.size()/2)));
                    const auto& second_half = std::stoull(std::string(key_str.begin() + (key_str.size()/2), key_str.end()));
                    tmp[first_half] += count;
                    tmp[second_half] += count;
                }
                else {
                    tmp[key * 2024] += count;
                }
            }
            stone_counts = tmp;
        }
        uint64_t result{0};
        for (const auto& [key, count] : stone_counts) {
            result += count;
        }
        return result;
    }
}

#endif //AOC2024_DAY11_HPP
