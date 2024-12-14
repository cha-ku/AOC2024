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

    enum class Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    auto get_direction_str(Direction direction)
    {
        std::string direction_str;
        switch(direction)
        {
            case Direction::UP:
                direction_str = "up";
                break;
            case Direction::RIGHT:
                direction_str = "right";
                break;
            case Direction::DOWN:
                direction_str = "down";
                break;
            case Direction::LEFT:
                direction_str = "left";
                break;
        }
        return direction_str;
    }

    struct Guard
    {
        int r;
        int c;
        Direction direction;

        constexpr auto turn_right()
        {
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
    };

    std::ostream& operator<<(std::ostream& os, const Guard& g)
    {
        os << "(" << g.r << "," << g.c << ") " << get_direction_str(g.direction);
        return os;
    }

    auto equals = [](const Guard& first, const Guard& second)
    {
        return first.r == second.r and first.c == second.c and first.direction == second.direction;
    };

    auto hash = [](const Guard& guard) {
        std::string hash_str{std::to_string(guard.r) + std::to_string(guard.c) + get_direction_str(guard.direction)};
        return std::hash<std::string>()(hash_str);
    };

    auto get_start_position(const std::vector<std::string>& input)
    {
        for(const auto& [index, str] : std::views::enumerate(input))
        {
            if (auto pos = str.find("^"); pos != std::string::npos)
            {
                return Guard(static_cast<int>(index), static_cast<int>(pos), Direction::UP);
            }
            if (auto pos = str.find(">"); pos != std::string::npos)
            {
                return Guard(static_cast<int>(index), static_cast<int>(pos), Direction::RIGHT);
            }
            if (auto pos = str.find("v"); pos != std::string::npos)
            {
                return Guard(static_cast<int>(index), static_cast<int>(pos), Direction::DOWN);
            }
            if (auto pos = str.find("<"); pos != std::string::npos)
            {
                return Guard(static_cast<int>(index), static_cast<int>(pos), Direction::LEFT);
            }
        }
        return Guard();
    }

    auto get_unique_positions(const std::vector<std::string>& input)
    {
        auto guard = get_start_position(input);
        auto num_cols = input[0].size();
        auto num_rows = input.size();
        std::unordered_set<Guard, decltype(hash), decltype(equals)> uniq;
        while(guard.r < num_rows and guard.r >= 0 and guard.c < num_cols and guard.c >= 0)
        {
            uniq.emplace(guard);
            if (guard.direction == Direction::UP)
            {
                if (guard.r == 0)
                {
                    break;
                }
                if (input[guard.r-1][guard.c] == '#')
                {
                    guard.turn_right();
                }
                else
                {
                    --guard.r;
                }
            }
            if (guard.direction == Direction::RIGHT) {
                if (guard.c == num_cols-1)
                {
                    break;
                }
                if (input[guard.r][guard.c+1] == '#')
                {
                    guard.turn_right();
                }
                else
                {
                    ++guard.c;
                }
            }
            if (guard.direction == Direction::DOWN)
            {
                if (guard.r == num_rows-1)
                {
                    break;
                }
                if (input[guard.r+1][guard.c] == '#')
                {
                    guard.turn_right();
                }
                else
                {
                    ++guard.r;
                }
            }
            if (guard.direction == Direction::LEFT)
            {
                if (guard.c == 0)
                {
                    break;
                }
                if (input[guard.r][guard.c-1] == '#')
                {
                    guard.turn_right();
                }
                else
                {
                    --guard.c;
                }
            }
        }
        return uniq;
    }

    auto get_unique_positions_count(const auto& test_input)
    {
        const auto& uniq = aoc::day06::get_unique_positions(test_input);
        auto print_input = test_input;
        auto result{0};
        for(const auto& u : uniq)
        {
            if (print_input[u.r][u.c] != 'X')
            {
                print_input[u.r][u.c] = 'X';
                result++;
            }
        }
        return result;
    }

    auto has_loop(std::vector<std::string>& input, const Guard& guard_start_position)
    {
        const auto num_rows = input.size();
        const auto num_cols = input[0].size();
        Guard guard = guard_start_position;
        std::unordered_set<Guard, decltype(hash), decltype(equals)> uniq{};
        bool start_position{true};
        while(guard.r < num_rows and guard.r >= 0 and guard.c < num_cols and guard.c >= 0)
        {
            if (uniq.contains(guard))
            {
                return true;
            }
            if (!start_position)
            {
                uniq.emplace(guard);
            }
            start_position = false;
            if (guard.direction == Direction::UP)
            {
                if (guard.r == 0)
                {
                    break;
                }
                if (input[guard.r-1][guard.c] == '#')
                {
                    guard.turn_right();
                    input[guard.r][guard.c] = '+';
                }
                else
                {
                    --guard.r;
                    input[guard.r][guard.c] = '|';
                }
            }
            if (guard.direction == Direction::RIGHT) {
                if (guard.c == num_cols-1)
                {
                    break;
                }
                if (input[guard.r][guard.c+1] == '#')
                {
                    guard.turn_right();
                    input[guard.r][guard.c] = '+';
                }
                else
                {
                    ++guard.c;
                    input[guard.r][guard.c] = '-';
                }
            }
            if (guard.direction == Direction::DOWN)
            {
                if (guard.r == num_rows-1)
                {
                    break;
                }
                if (input[guard.r+1][guard.c] == '#')
                {
                    guard.turn_right();
                    input[guard.r][guard.c] = '+';
                }
                else
                {
                    ++guard.r;
                    input[guard.r][guard.c] = '|';
                }
            }
            if (guard.direction == Direction::LEFT)
            {
                if (guard.c == 0)
                {
                    break;
                }
                if (input[guard.r][guard.c-1] == '#')
                {
                    guard.turn_right();
                    input[guard.r][guard.c] = '+';
                }
                else
                {
                    --guard.c;
                    input[guard.r][guard.c] = '-';
                }
            }
        }
        return false;
    }

    auto get_num_possible_obstruction_locations(const std::vector<std::string>& input)
    {
        const auto& start_position = get_start_position(input);
        uint64_t result{0};
        auto input_copy = input;
        const auto& all_traversal_locations = get_unique_positions(input);
        std::vector<Guard> unique_visited_locations;
        for(const auto& loc : all_traversal_locations)
        {
            if (input_copy[loc.r][loc.c] != 'X')
            {
                unique_visited_locations.emplace_back(loc);
                input_copy[loc.r][loc.c] = 'X';
            }

        }
        for (const auto& location : unique_visited_locations)
        {
            if (location.r == start_position.r and location.c == start_position.c)
            {
                continue;
            }
            auto input_copy2 = input;
            input_copy2[location.r][location.c] = '#';
            if (has_loop(input_copy2, start_position))
            {
                ++result;
            }
        }
        return result;
    }
}

#endif //AOC2024_DAY06_HPP
