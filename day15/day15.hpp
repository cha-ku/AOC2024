//
// Created by chaku on 01/01/25.
//

#ifndef AOC2024_DAY15_HPP
#define AOC2024_DAY15_HPP

#include <ranges>

namespace aoc::day15 {
    enum class dir {
        left,
        right,
        up,
        down
    };

    void move_left_robot1(std::vector<std::string>& input, int& robot_x, const int& robot_y) {
        const auto orig_robot_x = robot_x;
        if (input[robot_y][robot_x-1] == '.') {
            // draw robot in empty space
            input[robot_y][robot_x-1] = input[robot_y][orig_robot_x];
            input[robot_y][orig_robot_x] = '.';
            robot_x = robot_x-1;
            return;
        }
        if (input[robot_y][robot_x-1] == 'O') {
            while(input[robot_y][robot_x-1] == 'O') {
                robot_x = robot_x-1;
            }
            // all boxes stacked up to the wall
            if (input[robot_y][robot_x-1] == '#') {
                robot_x = orig_robot_x;
                return;
            }
            // we found an empty space
            const auto empty_space_x = robot_x-1;
            for (int i = empty_space_x; i < orig_robot_x; ++i) {
                input[robot_y][i] = input[robot_y][i+1];
            }
            input[robot_y][orig_robot_x] = '.';
            robot_x = orig_robot_x-1;
        }
    }

    void move_up_robot1(std::vector<std::string>& input, const int& robot_x, int& robot_y) {
        const auto orig_robot_y = robot_y;
        if (input[robot_y-1][robot_x] == '.') {
            // draw robot in empty space
            input[robot_y-1][robot_x] = input[orig_robot_y][robot_x];
            input[orig_robot_y][robot_x] = '.';
            robot_y = robot_y-1;
            return;
        }
        if (input[robot_y-1][robot_x] == 'O') {
            while(input[robot_y-1][robot_x] == 'O') {
                robot_y = robot_y-1;
            }
            // all boxes stacked up to the wall
            if (input[robot_y-1][robot_x] == '#') {
                robot_y = orig_robot_y;
                return;
            }
            // we found an empty space
            const auto empty_space_y = robot_y-1;
            for (int i = empty_space_y; i < orig_robot_y; ++i) {
                input[i][robot_x] = input[i+1][robot_x];
            }
            input[orig_robot_y][robot_x] = '.';
            robot_y = orig_robot_y-1;
        }
    }

    void move_right_robot1(std::vector<std::string>& input, int& robot_x, const int& robot_y) {
        const auto orig_robot_x = robot_x;
        if (input[robot_y][robot_x+1] == '.') {
            // draw robot in empty space
            input[robot_y][robot_x+1] = input[robot_y][orig_robot_x];
            input[robot_y][orig_robot_x] = '.';
            robot_x = robot_x+1;
            return;
        }
        if (input[robot_y][robot_x+1] == 'O') {
            while(input[robot_y][robot_x+1] == 'O') {
                robot_x = robot_x+1;
            }
            // all boxes stacked up to the wall
            if (input[robot_y][robot_x+1] == '#') {
                robot_x = orig_robot_x;
                return;
            }
            // we found an empty space
            const auto empty_space_x = robot_x+1;
            for (int i = empty_space_x; i > orig_robot_x; --i) {
                input[robot_y][i] = input[robot_y][i-1];
            }
            input[robot_y][orig_robot_x] = '.';
            robot_x = orig_robot_x+1;
        }
    }

    void move_down_robot1(std::vector<std::string>& input, const int& robot_x, int& robot_y) {
        const auto orig_robot_y = robot_y;
        if (input[robot_y+1][robot_x] == '.') {
            // draw robot in empty space
            input[robot_y+1][robot_x] = input[orig_robot_y][robot_x];
            input[orig_robot_y][robot_x] = '.';
            robot_y = robot_y+1;
            return;
        }
        if (input[robot_y+1][robot_x] == 'O') {
            while(input[robot_y+1][robot_x] == 'O') {
                robot_y = robot_y+1;
            }
            // all boxes stacked up to the wall
            if (input[robot_y+1][robot_x] == '#') {
                robot_y = orig_robot_y;
                return;
            }
            // we found an empty space
            const auto empty_space_y = robot_y+1;
            for (int i = empty_space_y; i > orig_robot_y; --i) {
                input[i][robot_x] = input[i-1][robot_x];
            }
            input[orig_robot_y][robot_x] = '.';
            robot_y = orig_robot_y+1;
        }
    }

    void move_robot1(std::vector<std::string>& input, int& robot_x, int& robot_y, const dir move) {
        switch(move) {
            case dir::left:
                move_left_robot1(input, robot_x, robot_y);
                break;
            case dir::down:
                move_down_robot1(input, robot_x, robot_y);
                break;
            case dir::right:
                move_right_robot1(input, robot_x, robot_y);
                break;
            case dir::up:
                move_up_robot1(input, robot_x, robot_y);
                break;
        }
    }

    void move_left_robot2(std::vector<std::string>& input, int& robot_x, const int& robot_y) {
        const auto orig_robot_x = robot_x;
        if (input[robot_y][robot_x-1] == '.') {
            // draw robot in empty space
            input[robot_y][robot_x-1] = input[robot_y][orig_robot_x];
            input[robot_y][orig_robot_x] = '.';
            robot_x = robot_x-1;
            return;
        }
        if (input[robot_y][robot_x-1] == ']') {
            while(input[robot_y][robot_x-1] == '[' || input[robot_y][robot_x-1] == ']') {
                robot_x = robot_x-1;
            }
            // all boxes stacked up to the wall
            if (input[robot_y][robot_x-1] == '#') {
                robot_x = orig_robot_x;
                return;
            }
            // we found an empty space
            const auto empty_space_x = robot_x-1;
            for (int i = empty_space_x; i < orig_robot_x; ++i) {
                input[robot_y][i] = input[robot_y][i+1];
            }
            input[robot_y][orig_robot_x] = '.';
            robot_x = orig_robot_x-1;
        }
    }

    void move_up_robot2(std::vector<std::string>& input, const int& robot_x, int& robot_y) {
        const auto orig_robot_y = robot_y;
        if (input[robot_y-1][robot_x] == '.') {
            // draw robot in empty space
            input[robot_y-1][robot_x] = input[orig_robot_y][robot_x];
            input[orig_robot_y][robot_x] = '.';
            robot_y = robot_y-1;
            return;
        }
        if (input[robot_y-1][robot_x] == '[' || input[robot_y-1][robot_x] == ']') {
            while(input[robot_y-1][robot_x] == '[' || input[robot_y-1][robot_x] == ']') {
                robot_y = robot_y-1;
            }
            // all boxes stacked up to the wall
            if (input[robot_y-1][robot_x] == '#') {
                robot_y = orig_robot_y;
                return;
            }
            // we found an empty space
            const auto empty_space_y = robot_y-1;
            for (int i = empty_space_y; i < orig_robot_y; ++i) {
                input[i][robot_x] = input[i+1][robot_x];
            }
            input[orig_robot_y][robot_x] = '.';
            robot_y = orig_robot_y-1;
        }
    }

    void move_right_robot2(std::vector<std::string>& input, int& robot_x, const int& robot_y) {
        const auto orig_robot_x = robot_x;
        if (input[robot_y][robot_x+1] == '.') {
            // draw robot in empty space
            input[robot_y][robot_x+1] = input[robot_y][orig_robot_x];
            input[robot_y][orig_robot_x] = '.';
            robot_x = robot_x+1;
            return;
        }
        if (input[robot_y][robot_x+1] == '[') {
            while(input[robot_y][robot_x+1] == '[' || input[robot_y][robot_x+1] == ']') {
                robot_x = robot_x+1;
            }
            // all boxes stacked up to the wall
            if (input[robot_y][robot_x+1] == '#') {
                robot_x = orig_robot_x;
                return;
            }
            // we found an empty space
            const auto empty_space_x = robot_x+1;
            for (int i = empty_space_x; i > orig_robot_x; --i) {
                input[robot_y][i] = input[robot_y][i-1];
            }
            input[robot_y][orig_robot_x] = '.';
            robot_x = orig_robot_x+1;
        }
    }

    void move_down_robot2(std::vector<std::string>& input, const int& robot_x, int& robot_y) {
        const auto orig_robot_y = robot_y;
        if (input[robot_y+1][robot_x] == '.') {
            // draw robot in empty space
            input[robot_y+1][robot_x] = input[orig_robot_y][robot_x];
            input[orig_robot_y][robot_x] = '.';
            robot_y = robot_y+1;
            return;
        }
        if (input[robot_y+1][robot_x] == '[' || input[robot_y+1][robot_x] == ']') {
            while(input[robot_y+1][robot_x] == '[' || input[robot_y+1][robot_x] == ']') {
                robot_y = robot_y+1;
            }
            // all boxes stacked up to the wall
            if (input[robot_y+1][robot_x] == '#') {
                robot_y = orig_robot_y;
                return;
            }
            // we found an empty space
            const auto empty_space_y = robot_y+1;
            for (int i = empty_space_y; i > orig_robot_y; --i) {
                input[i][robot_x] = input[i-1][robot_x];
            }
            input[orig_robot_y][robot_x] = '.';
            robot_y = orig_robot_y+1;
        }
    }

    void move_robot2(std::vector<std::string>& input, int& robot_x, int& robot_y, const dir move) {
        switch(move) {
            case dir::left:
                move_left_robot2(input, robot_x, robot_y);
                break;
            case dir::down:
                move_down_robot2(input, robot_x, robot_y);
                break;
            case dir::right:
                move_right_robot2(input, robot_x, robot_y);
                break;
            case dir::up:
                move_up_robot2(input, robot_x, robot_y);
                break;
        }
    }

    constexpr auto char_to_direction(const char c) -> dir {
        switch(c) {
            case '<':
                return dir::left;
            case 'v':
                return dir::down;
            case '>':
                return dir::right;
            case '^':
                return dir::up;
            default:
                throw std::invalid_argument("Bad character passed\n");
        }
    }

    auto convert_map(const std::vector<std::string>& input) -> std::vector<std::string> {
        std::vector<std::string> converted_map;
        for (const auto& line : input) {
            std::string converted_line;
            for (const auto& c : line) {
                if (c == '#') {
                    converted_line += "##";
                }
                if (c == 'O') {
                    converted_line += "[]";
                }
                if (c == '.') {
                    converted_line += "..";
                }
                if (c == '@') {
                    converted_line += "@.";
                }
            }
            converted_map.emplace_back(converted_line);
        }
        return converted_map;
    }

    auto get_robot_position(const std::vector<std::string>& grid) -> std::tuple<int, int> {
        for (int y = 0; y < grid.size(); ++y) {
            for (int x = 0; x < grid[0].size(); ++x) {
                if (grid[y][x] == '@') {
                    return {x, y};
                }
            }
        }
        return {-1, -1};
    }

    auto get_gps_score(const std::vector<std::string>& final_state, const char box) {
        uint64_t result{0};
        for (int y = 0; y < final_state.size(); ++y) {
            for (int x = 0; x < final_state[0].size(); ++x) {
                if (final_state[y][x] == box) {
                    result += 100*y + x;
                }
            }
        }
        return result;
    }

    auto sum_of_gps_coordinates(std::vector<std::string>& input, const std::string& moves, bool part2 = false) -> uint64_t {
        int robot_x{-1};
        int robot_y{-1};
        //auto part2_input = convert_map(input);
        std::vector<std::string> part2_input {
                "##############",
                "##......##..##",
                "##..........##",
                "##...[][]...##",
                "##....[]....##",
                "##.....@....##",
                "##############"
        };
        std::string test_moves{"^"};
        std::cout << "initial state\n";
        for (const auto& line : part2_input) {
            std::cout << line << "\n";
        }
        std::cout << "\n";
        if (part2) {
            const auto& [x_, y_] = get_robot_position(part2_input);
            robot_x = x_;
            robot_y = y_;
        }
        else {
            const auto& [x_, y_] = get_robot_position(input);
            robot_x = x_;
            robot_y = y_;
        }

        for (const auto& [idx, c]: std::views::enumerate(test_moves)) {
            const dir d = char_to_direction(c);
            if (part2) {
                std::cout << idx << ": " << c << " (" << robot_y << "," << robot_x << ")\n";
                move_robot2(part2_input, robot_x, robot_y, d);
                for (const auto& line : part2_input) {
                    std::cout << line << "\n";
                }
                std::cout << "\n";
            }
            else {
                move_robot1(input, robot_x, robot_y, d);
            }
        }
        if (part2) {
            return get_gps_score(part2_input, '[');
        }
        else {
            return get_gps_score(input, 'O');
        }
    }
}

#endif //AOC2024_DAY15_HPP
