//
// Created by chaku on 10/12/24.
//

#ifndef AOC2024_DAY05_HPP
#define AOC2024_DAY05_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>


namespace aoc::day05 {
    [[maybe_unused]] const auto print = [](const auto& container) {
        std::for_each(container.cbegin(), container.cend(), [](const auto& elem) {
            std::cout << elem << ",";
        });
        std::cout << "\n";
    };

    using ui64 = uint64_t;

    struct before_and_after {
        int element;
        std::vector<int> after_element;
        std::vector<int> before_element;
    };
    auto process_text(std::string& txt)  {
        std::stringstream ss(txt);
        std::string line;
        std::unordered_map<int, std::unordered_set<int>> element_before_after_relation;
        std::vector<std::vector<int>> updates;

        constexpr auto as_int = std::views::transform([&](const auto& elem) {
            return std::stoi(std::ranges::to<std::string>(elem));});

        using std::operator""sv;
        constexpr auto update_delim{","sv};
        constexpr auto rule_delim{"|"sv};
        while(std::getline(ss, line)) {
            if (line.find(rule_delim) != std::string::npos) {
                std::vector<int> rule;
                for (auto rule_elem : std::views::split(line, rule_delim) | as_int) {
                    rule.emplace_back(rule_elem);
                }
                if (element_before_after_relation.contains(rule[0])) {
                    element_before_after_relation[rule[0]].emplace(rule[1]);
                }
                else {
                    element_before_after_relation[rule[0]] = {rule[1]};
                }

//                std::cout << "rule - ";
//                print(rule);
            }
            else if (line.find(update_delim) != std::string::npos) {
                std::vector<int> update;
                for (auto update_elem : std::views::split(line, update_delim) | as_int) {
                    update.emplace_back(update_elem);
                }
                updates.emplace_back(update);

//                std::cout << "update - ";
//                print(update);
            }
        }

//        for (auto& [key, value] : element_before_after_relation) {
//            std::cout << key << " : ";
//            print(value);
//        }
        return std::make_tuple(updates, element_before_after_relation);
    }

    auto is_correctly_ordered(std::vector<int>& update, std::unordered_map<int, std::unordered_set<int>>& relations)  {
        for(auto i = 0; i < update.size(); ++i) {
            const auto& element = update[i];
            const auto& should_come_after = relations[element];
            for (auto j = i+1; j < update.size(); ++j) {
                if (!should_come_after.contains(update[j])) {
                    return false;
                }
            }
        }
        return true;
    }

    auto get_incorrect_order_index(std::vector<int>& update, std::unordered_map<int, std::unordered_set<int>>& relations)  {
        for(auto i = 0; i < update.size(); ++i) {
            const auto& element = update[i];
            const auto& should_come_after = relations[element];
            for (auto j = i+1; j < update.size(); ++j) {
                if (!should_come_after.contains(update[j])) {
                    return std::make_pair(i, j);
                }
            }
        }
        return std::make_pair(-1, -1);
    }

    auto sum_of_correctly_ordered_middle_pages(std::string& input_text) {
        ui64 result{0};
        auto [updates, relations] = process_text(input_text);
        for(auto& update : updates) {
            if (is_correctly_ordered(update, relations)) {
                result += update[static_cast<size_t>(update.size()/2)];
            }
        }
        return result;
    }

    auto sum_of_fixed_incorrectly_ordered_middle_pages(std::string& input_text) {
        ui64 result{0};
        auto [updates, relations] = process_text(input_text);
        for(auto& update : updates) {
            auto [idx1, idx2] = get_incorrect_order_index(update, relations);
            if (idx1 == idx2) {
                continue;
            }
            auto to_be_fixed = update;
            while (idx1 != idx2) {
                std::swap(to_be_fixed[idx1], to_be_fixed[idx2]);
                const auto& [idx1_1, idx2_2] = get_incorrect_order_index(to_be_fixed, relations);
                idx1 = idx1_1;
                idx2 = idx2_2;
            }
            result += to_be_fixed[static_cast<size_t>(to_be_fixed.size()/2)];
        }
        return result;
    }
}

#endif //AOC2024_DAY05_HPP
