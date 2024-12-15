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

    auto parse_input_line(const std::string& line, std::unordered_map<uint64_t, std::vector<uint64_t>>& parsed)
    {
        constexpr auto test_value_delim = R"(:)";
        const auto test_value_found = line.find(test_value_delim);
        const uint64_t test_value = std::stoul(line.substr(0, test_value_found));
        const auto& str_operators = line.substr(test_value_found+1);
        auto number_vec = str_operators
                          | std::ranges::views::split(' ')
                          | std::ranges::views::transform([](auto&& num_str) {
                                std::string_view sv(num_str.begin(), num_str.end());
                                std::string str{sv};
                                // NOLINTNEXTLINE
                                return str.size() == 0 ? 0 : std::stoul(str); })
                          | std::ranges::to<std::vector>();
        number_vec.erase(std::remove_if(number_vec.begin(), number_vec.end(), [](const auto& elem) { return elem == 0; }));
        parsed[test_value] = number_vec;
    }

    auto generate_all_combinations(uint64_t container_size) {
        uint64_t max_operations = std::pow(2, container_size);
        std::vector<std::vector<uint8_t>> operations;
        uint64_t start{0};
        while(start < max_operations) {
            std::vector<uint8_t> bool_repr(container_size-1, false);
            uint64_t x{0};
            while(x <= start)
            {
                if (1 << x & start)
                {
                    bool_repr[x] = true;
                }
                else
                {
                    bool_repr[x] = false;
                }
                ++x;
            }
            operations.emplace_back(bool_repr);
            ++start;
        }
        return operations;
    }

    auto calibration_result_is_true(const uint64_t& test, const std::vector<uint64_t>& test_values)
    {
        const auto all_combinations = generate_all_combinations(test_values.size());
        for(const auto& combination : all_combinations)
        {
            uint64_t combination_result{test_values[0]};
            for(size_t i = 0; i < combination.size(); ++i)
            {
                combination[i] ? combination_result *= test_values[i+1] : combination_result += test_values[i+1];
                if (combination_result == test)
                {
                    return true;
                }
            }
        }
        return false;
    }

    auto calibration_result_if_true(const std::vector<std::string>& test_input) -> uint64_t
    {
        std::unordered_map<uint64_t, std::vector<uint64_t>> parsed;
        std::for_each(test_input.cbegin(), test_input.cend(), [&](const auto& line) {
            parse_input_line(line, parsed);
        });
        long long unsigned result{0};
        for(const auto& [test_value, puzzle_input_values]: parsed)
        {
            if (calibration_result_is_true(test_value, puzzle_input_values))
            {
                result += test_value;
            }

        }
        return result;
    }
}

#endif //AOC2024_DAY07_HPP
