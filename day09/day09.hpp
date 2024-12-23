//
// Created by chaku on 22/12/24.
//

#ifndef AOC2024_DAY09_HPP
#define AOC2024_DAY09_HPP

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <ranges>

namespace aoc::day09 {
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

    using u64 = uint64_t;

    auto generate_representation(const std::string& input) -> std::vector<int> {
        std::vector<int> result;
        u64 index{0};
        for (size_t pos = 0; pos < input.size(); ++pos) {
            auto num = input[pos] - '0';
            bool is_block = pos % 2 == 0;
            while(num > 0) {
                result.emplace_back(is_block ? index : -1);
                --num;
            }
            if (is_block) {
                ++index;
            }
        }
        return result;
    }

    auto move_file_blocks(std::vector<int>&& generated) -> std::vector<int> {
        std::vector<size_t> blanks;
        for (const auto& [idx , x] : std::views::enumerate(generated)) {
            if(x == -1) {
                blanks.emplace_back(idx);
            }
        }

        size_t right{generated.size()-1};
        for(const auto& left : blanks) {
            while(generated[right] == -1) {
                right--;
            }
            if (right <= left) {
                break;
            }
            generated[left] = generated[right];
            generated[right] = -1;
        }
        return generated;
    }

    auto get_checksum(const std::string& input) -> u64 {
        const auto& processed = move_file_blocks(generate_representation(input));
        u64 result{0};
        for (size_t i = 0; i < processed.size(); ++i) {
            if (processed[i] != -1) {
                result += processed[i] * i;
            }
        }
        return result;
    }
}

#endif //AOC2024_DAY09_HPP
