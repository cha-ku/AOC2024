//
// Created by chaku on 31/12/24.
//

#ifndef AOC2024_DAY14_HPP
#define AOC2024_DAY14_HPP

#include <cmath>
#include <string>
#include <vector>

#include <ctre.hpp>
#include <ranges>
#include <filesystem>

namespace aoc::day14 {
    auto get_position_velocity(const std::string& str) -> std::tuple<int, int, int, int> {
        using namespace ctre::literals;
        auto [whole, p_x, p_y, v_x, v_y] =
                ctre::match<"p=([0-9]+),([0-9]+) v=(-?[0-9]+),(-?[0-9]+)">(str);
        const int& px = p_x.to_number();
        const int& py = p_y.to_number();
        const int& vx = v_x.to_number();
        const int& vy = v_y.to_number();
        return {px, py, vx, vy};
    }

    auto get_safety_factor(const std::vector<std::string>& robots, const int height, const int width, const uint64_t num_seconds)-> uint64_t {
        uint64_t result{0};
        auto mid_x = width/2;
        auto mid_y = height/2;
        std::vector<std::pair<int, int>> first_quadrant;
        std::vector<std::pair<int, int>> second_quadrant;
        std::vector<std::pair<int, int>> third_quadrant;
        std::vector<std::pair<int, int>> fourth_quadrant;
        for (const auto& robot : robots) {
            const auto& [px, py, vx, vy] = get_position_velocity(robot);
            int dx = static_cast<int>((px + (num_seconds * vx))) % width;
            if (dx < 0) {
                dx += width;
            }
            int dy = static_cast<int>((py + (num_seconds * vy))) % height;
            if (dy < 0) {
                dy += height;
            }
            if (dx < mid_x && dy < mid_y) {
                first_quadrant.emplace_back(dx, dy);
            }
            else if (dx > mid_x && dy < mid_y) {
                second_quadrant.emplace_back(dx, dy);
            }
            else if (dx > mid_x && dy > mid_y) {
                third_quadrant.emplace_back(dx, dy);
            }
            else if (dx < mid_x && dy > mid_y) {
                fourth_quadrant.emplace_back(dx, dy);
            }
        }
        result = first_quadrant.size() * second_quadrant.size() * third_quadrant.size() * fourth_quadrant.size();
        return result;
    }

    struct Robot {
        int px;
        int py;
        int vx;
        int vy;
    };

    auto check_easter_egg(const std::vector<std::string>& robots, const int height, const int width) -> uint64_t {
        const bool debug{false};
        std::vector<Robot> robot_list;
        for (const auto& robot : robots) {
            const auto& [px, py, vx, vy] = get_position_velocity(robot);
            robot_list.emplace_back(px, py, vx, vy);
        }
        const std::string row(width, ' ');

        for (const auto& sec : std::views::iota(0) | std::views::take(10000/*height * width*/)) {
            std::vector<std::string> viz(height, row);
            for (const auto& [index, r] : std::views::enumerate(robot_list)) {
                int dx = static_cast<int>((r.px + (sec * r.vx))) % width;
                if (dx < 0) {
                    dx += width;
                }
                int dy = static_cast<int>((r.py + (sec * r.vy))) % height;
                if (dy < 0) {
                    dy += height;
                }
                viz[dy][dx] = '*';
            }
            auto found = std::find_if(viz.begin(), viz.end(), [](const auto& v) {
                return v.find("**********") != std::string::npos;
            });
            if (found != viz.end()) {
                if (debug) {
                    std::for_each(viz.begin(), viz.end(), [](const auto& v) {
                        std::cout << v << "\n";
                    });
                }
                return sec;
            }
        }
        return 0;
    }
}

#endif //AOC2024_DAY14_HPP