//
// Created by chaku on 14/12/24.
//

#ifndef AOC2024_DAY07_HPP
#define AOC2024_DAY07_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <unordered_set>
#include <cmath>


namespace aoc::day07 {
    [[maybe_unused]] auto print (const auto& container) {
        size_t index{0};
        const size_t sz{container.size()};
        std::for_each(container.cbegin(), container.cend(), [&] (const auto& elem) {
            std::cout << elem ;
            if (index != sz-1)
            {
                std::cout << ", ";
                index++;
            }
        });
        std::cout << "\n";
    };

    using ull = unsigned long long;

    auto parse_input_line(const std::string& line) -> std::pair<ull, std::vector<ull>>
    {
        constexpr auto test_value_delim = R"(:)";
        const auto test_value_found = line.find(test_value_delim);
        const ull test_value = std::stoull(line.substr(0, test_value_found));
        const auto& str_operators = line.substr(test_value_found+1);
        auto number_vec = str_operators
                          | std::ranges::views::split(' ')
                          | std::ranges::views::transform([](auto&& num_str) {
                                std::string_view sv(num_str.begin(), num_str.end());
                                std::string str{sv};
                                // NOLINTNEXTLINE
                                return str.size() == 0 ? 0 : std::stoull(str); })
                          | std::ranges::to<std::vector>();
        number_vec.erase(std::remove_if(number_vec.begin(), number_vec.end(), [](const auto& elem) { return elem == 0; }));
        return std::make_pair(test_value, number_vec);
    }

    auto check(const ull& test, const std::vector<ull>& test_values, const size_t current_index, ull curr_result, bool concat) -> bool
    {
        auto concat_two_numbers = [](ull num1, ull num2) {
            return std::stoull(std::to_string(num1) + std::to_string(num2));
        };

        if (current_index == test_values.size() - 1)
        {
            auto part_1 = (curr_result * test_values[current_index]) == test || (curr_result + test_values[current_index]) == test;
            if (concat)
            {
                return  part_1 || (concat_two_numbers(curr_result, test_values[current_index]) == test);
            }
            return part_1;
        }
        if (concat)
        {
            return check(test, test_values, current_index+1, curr_result * test_values[current_index], concat)
                    ||
                    check(test, test_values, current_index+1, curr_result + test_values[current_index], concat)
                    ||
                    check(test, test_values, current_index+1, concat_two_numbers(curr_result, test_values[current_index]), concat);

        }
        return check(test, test_values, current_index+1, curr_result * test_values[current_index], concat)
               || check(test, test_values, current_index+1, curr_result + test_values[current_index], concat);
    }

    auto calibration_result_is_true(const ull &test, const std::vector<ull> &test_values, bool concat)
    {
        ull curr_result = test_values[0];
        return check(test, test_values, 1, curr_result, concat);
    }

    auto calibration_result_if_true(const std::vector<std::string>& test_input, bool concat=false) -> ull
    {
        ull result{0};
        std::for_each(test_input.cbegin(), test_input.cend(), [&](const auto& line) {
            const auto& [test_value, puzzle_input_values] = parse_input_line(line);
            if (calibration_result_is_true(test_value, puzzle_input_values, concat))
            {
                result += test_value;
            }
        });
        return result;
    }
}

#endif //AOC2024_DAY07_HPP
