//
// Created by chaku on 25/12/24.
//

#ifndef AOC2024_DAY10_HPP
#define AOC2024_DAY10_HPP

#include <iostream>
#include <cstdint>
#include <set>
#include <deque>
#include <stack>

namespace aoc::day10 {
    [[maybe_unused]] auto print(const auto &container) {
        size_t index{0};
        const size_t sz{container.size()};
        std::for_each(container.cbegin(), container.cend(), [&](const auto &elem) {
            std::cout << elem;
            if (index != sz - 1) {
                std::cout << ", ";
                index++;
            }
        });
        std::cout << "\n";
    };


    using ui64 = uint64_t;
    void check_part1(const std::vector<std::string> &topographic_map, const size_t num_rows, const size_t num_cols,
                     std::pair<int, int> &&to_be_visited, std::set<std::pair<int, int>> &found_nines, ui64 &result) {
        const auto &[row, col] = to_be_visited;
        int curr_value = topographic_map[row][col] - '0';
        if (curr_value == 9) {
            if (!found_nines.contains(std::pair(row, col))) {
                found_nines.emplace(row, col);
                result += 1;
                return;
            }
        }
        if ((row + 1) < num_rows && topographic_map[row + 1][col] - '0' == curr_value + 1) {
            check_part1(topographic_map, num_rows, num_cols, std::make_pair(row + 1, col), found_nines, result);
        }
        if ((row - 1) >= 0 && topographic_map[row - 1][col] - '0' == curr_value + 1) {
            check_part1(topographic_map, num_rows, num_cols, std::make_pair(row - 1, col), found_nines, result);
        }
        if ((col + 1) < num_cols && topographic_map[row][col + 1] - '0' == curr_value + 1) {
            check_part1(topographic_map, num_rows, num_cols, std::make_pair(row, col + 1), found_nines, result);
        }
        if ((col - 1) >= 0 && topographic_map[row][col - 1] - '0' == curr_value + 1) {
            check_part1(topographic_map, num_rows, num_cols, std::make_pair(row, col - 1), found_nines, result);
        }
    }

    auto sum_of_trailheads(const auto &topographic_map) -> uint64_t {
        uint64_t result{0};

        const auto num_rows = topographic_map.size();
        const auto num_cols = topographic_map[0].size();

        for (int r = 0; r < num_rows; ++r) {
            for (int c = 0; c < num_cols; ++c) {
                if (topographic_map[r][c] == '0') {
                    uint64_t local = 0;
                    std::set<std::pair<int, int>> found;
                    check_part1(topographic_map, num_rows, num_cols, std::make_pair(r, c), found, local);
                    result += local;
                }
            }
        }
        return result;
    }

    void check_part2(const std::vector<std::string> &topographic_map, const size_t num_rows, const size_t num_cols,
                     std::pair<int, int> &&to_be_visited, std::set<std::pair<int, int>> &found_nines, ui64 &result) {
        const auto &[row, col] = to_be_visited;
        int curr_value = topographic_map[row][col] - '0';
        if (curr_value == 9) {
            result += 1;
            return;
        }
        if ((row + 1) < num_rows && topographic_map[row + 1][col] - '0' == curr_value + 1) {
            check_part2(topographic_map, num_rows, num_cols, std::make_pair(row + 1, col), found_nines, result);
        }
        if ((row - 1) >= 0 && topographic_map[row - 1][col] - '0' == curr_value + 1) {
            check_part2(topographic_map, num_rows, num_cols, std::make_pair(row - 1, col), found_nines, result);
        }
        if ((col + 1) < num_cols && topographic_map[row][col + 1] - '0' == curr_value + 1) {
            check_part2(topographic_map, num_rows, num_cols, std::make_pair(row, col + 1), found_nines, result);
        }
        if ((col - 1) >= 0 && topographic_map[row][col - 1] - '0' == curr_value + 1) {
            check_part2(topographic_map, num_rows, num_cols, std::make_pair(row, col - 1), found_nines, result);
        }
    }

    auto sum_of_ratings(const auto &topographic_map) -> uint64_t {
        uint64_t result{0};

        const auto num_rows = topographic_map.size();
        const auto num_cols = topographic_map[0].size();

        for (int r = 0; r < num_rows; ++r) {
            for (int c = 0; c < num_cols; ++c) {
                if (topographic_map[r][c] == '0') {
                    uint64_t local = 0;
                    std::set<std::pair<int, int>> found;
                    check_part2(topographic_map, num_rows, num_cols, std::make_pair(r, c), found, local);
                    result += local;
                }
            }
        }
        return result;
    }
}

#endif //AOC2024_DAY10_HPP
