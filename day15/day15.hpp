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

    // PART 1

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

    // PART 2

    struct delta {
        int x, y;
    };

    struct point2d {
        int x, y;
        constexpr friend auto operator <=>(const point2d&, const point2d&)=default;
        point2d operator+(const delta d) const {
            return {x+d.x, y+d.y};
        }
    };

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

    auto get_robot_position(const std::vector<std::string>& grid) -> point2d {
        for (int y = 0; y < grid.size(); ++y) {
            for (int x = 0; x < grid[0].size(); ++x) {
                if (grid[y][x] == '@') {
                    return {x, y};
                }
            }
        }
        return {-1, -1};
    }

    auto get_gps_score(const std::vector<std::string>& final_state, const char box) -> uint64_t {
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

    auto sum_of_gps_coordinates_part1(const std::vector<std::string>& test_input, const std::string& moves) -> uint64_t {
        auto input = test_input;
        int robot_x;
        int robot_y;
        const auto& [x_, y_] = get_robot_position(test_input);
        robot_x = x_;
        robot_y = y_;
        for (const auto& [idx, c]: std::views::enumerate(moves)) {
            const dir d = char_to_direction(c);
            move_robot1(input, robot_x, robot_y, d);
        }
        return get_gps_score(input, 'O');
    }

    auto sum_of_gps_coordinates_part2(const std::vector<std::string>& test_input, const std::string& moves) -> uint64_t {
        auto part2_input = convert_map(test_input);

        // check https://gist.github.com/philipplenk/d84faf2b1000497e2321fe5fc10b37da for original solution
        // and https://devblogs.microsoft.com/cppblog/cpp23-deducing-this/#recursive-lambdas for the `this auto` pattern
        const auto robot_can_move = [&](this auto&& self, point2d start, delta direction) -> bool {
            const auto target = start + direction;
            const auto target_location = part2_input[target.y][target.x];

            if (target_location == '#') {
                return false;
            }
            if (target_location == '.') {
                return true;
            }
            // check left or right
            if (direction.x != 0) {
                return self(target, direction);
            }

            // increase span if checking up or down
            const auto horizontal_neighbour = target_location == '[' ? delta(1, 0) : delta(-1, 0);
            return self(target, direction) && self(target + horizontal_neighbour, direction);
        };

        const auto move_robot = [&](this auto&& self, point2d start, delta direction) -> point2d {
            if (!robot_can_move(start, direction)) {
                return start;
            }

            const auto target = start + direction;
            const auto target_location = part2_input[target.y][target.x];

            if (target_location == '[' || target_location == ']') {
                self(target, direction);
                if (direction.x == 0) {
                    const auto horizontal_neighbour = target_location == '[' ? delta(1,0) : delta(-1, 0);
                    const auto neighbour_span = target + horizontal_neighbour;
                    self(neighbour_span, direction);
                    part2_input[neighbour_span.y][neighbour_span.x] = '.';
                }
            }
            part2_input[target.y][target.x] = part2_input[start.y][start.x];
            return target;
        };

        //std::cout << "initial state\n";
        //for (const auto& line : part2_input) {
        //    std::cout << line << "\n";
        //}
        //std::cout << "\n";

        auto robot_position = get_robot_position(part2_input);
        part2_input[robot_position.y][robot_position.x] = '.';
        for (const auto& [idx, c]: std::views::enumerate(moves)) {
            const dir d = char_to_direction(c);
            //std::cout << idx << ": " << c << " (" << robot_position.y << "," << robot_position.x << ")\n";
            switch(d) {
                case dir::left: robot_position = move_robot(robot_position, {-1, 0}); break;
                case dir::right: robot_position = move_robot(robot_position, {1, 0}); break;
                case dir::up: robot_position = move_robot(robot_position, {0, -1}); break;
                case dir::down: robot_position = move_robot(robot_position, {0, 1}); break;
            }
            //for (const auto& [indx, line] : std::views::enumerate(part2_input)) {
            //    std::cout << indx << " " << line << "\n";
            //}
            //std::cout << "\n";
        }
        return get_gps_score(part2_input, '[');
    }
}

#endif //AOC2024_DAY15_HPP
