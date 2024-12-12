//
// Created by chaku on 11/12/24.
//

#ifndef AOC2024_DAY06_HPP
#define AOC2024_DAY06_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <unordered_set>


namespace aoc::day06 {
    [[maybe_unused]] const auto print = [](const auto& container) {
        std::for_each(container.cbegin(), container.cend(), [](const auto& elem) {
            std::cout << elem << "\n";
        });
        std::cout << "\n";
    };

    using ui64 = uint64_t;

    enum class Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    struct Guard {
        int r;
        int c;
        Direction direction;

        constexpr auto turn_right() {
            switch(direction) {
                case Direction::UP:
                    direction = Direction::RIGHT;
                    return;
                case Direction::RIGHT:
                    direction = Direction::DOWN;
                    return;
                case Direction::DOWN:
                    direction = Direction::LEFT;
                    return;
                case Direction::LEFT:
                    direction = Direction::UP;
                    return;
            }
        }

        bool operator ==(const Guard& other) const {
            return r == other.r && c == other.c;
        }

        bool operator <(const Guard& other) const {
            if (r < other.r) {
                return true;
            }
            else if (r == other.r) {
                if (c < other.c) {
                    return true;
                }
            }
            return false;
        }
    };

    auto get_start_position(std::vector<std::string>& input) {
        for(const auto& [index, str] : std::views::enumerate(input)) {
            if (auto pos = str.find("^"); pos != std::string::npos) {
                return Guard(static_cast<int>(index), static_cast<int>(pos), Direction::UP);
            }
            if (auto pos = str.find(">"); pos != std::string::npos) {
                return Guard(static_cast<int>(index), static_cast<int>(pos), Direction::RIGHT);
            }
            if (auto pos = str.find("v"); pos != std::string::npos) {
                return Guard(static_cast<int>(index), static_cast<int>(pos), Direction::DOWN);
            }
            if (auto pos = str.find("<"); pos != std::string::npos) {
                return Guard(static_cast<int>(index), static_cast<int>(pos), Direction::LEFT);
            }
        }
        return Guard();
    }

    auto get_unique_positions(std::vector<std::string>& input) {
        auto guard = get_start_position(input);
        input[guard.r][guard.c] = '.';
        std::vector<Guard> visited;
        auto num_cols = input[0].size();
        auto num_rows = input.size();
        while(guard.r < num_rows and guard.r >= 0 and guard.c < num_cols and guard.c >= 0) {
            visited.emplace_back(guard);
            if (guard.direction == Direction::UP) {
                if (guard.r == 0) {
                    break;
                }
                if (input[guard.r-1][guard.c] == '.') {
                    --guard.r;
                }
                else {
                    guard.turn_right();
                }
            }
            if (guard.direction == Direction::RIGHT) {
                if (guard.c == num_cols-1) {
                    break;
                }
                if (input[guard.r][guard.c+1] == '.') {
                    ++guard.c;
                }
                else {
                    guard.turn_right();
                }
            }
            if (guard.direction == Direction::DOWN) {
                if (guard.r == num_rows-1) {
                    break;
                }
                if (input[guard.r+1][guard.c] == '.') {
                    ++guard.r;
                }
                else {
                    guard.turn_right();
                }
            }
            if (guard.direction == Direction::LEFT) {
                if (guard.c == 0) {
                    break;
                }
                if (input[guard.r][guard.c-1] == '.') {
                    --guard.c;
                }
                else {
                    guard.turn_right();
                }
            }
        }
        std::sort(visited.begin(), visited.end());
        auto last = std::unique(visited.begin(), visited.end());
        visited.erase(last, visited.end());
        return visited.size();
    }
}

#endif //AOC2024_DAY06_HPP
