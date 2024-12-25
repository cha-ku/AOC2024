//
// Created by chaku on 22/12/24.
//

#ifndef AOC2024_DAY09_HPP
#define AOC2024_DAY09_HPP

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <ranges>
#include <stack>
#include <print>

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
    using fileId_info = std::tuple<int, int, int>;

    std::stack<fileId_info> fileId_count;
    bool file_id_count_generated = false;
    auto generate_representation(const std::string& input) -> std::vector<int> {
        std::vector<int> result;
        u64 fileId{0};
        u64 fileId_index{0};
        for (size_t pos = 0; pos < input.size(); ++pos) {
            auto num = input[pos] - '0';
            bool is_block = pos % 2 == 0;
            if (is_block && !file_id_count_generated) {
                fileId_count.emplace(fileId, num, fileId_index);
            }
            while(num > 0) {
                result.emplace_back(is_block ? fileId : -1);
                --num;
                ++fileId_index;
            }
            if (is_block) {
                ++fileId;
            }
        }
        file_id_count_generated = true;
        return result;
    }

    auto move_file_blocks_2(std::vector<int>&& generated) -> std::vector<int> {
        while(!fileId_count.empty()) {
            const auto& [fileId, count, index] = fileId_count.top();
            fileId_count.pop();
            auto generated_until_index =  std::ranges::take_while_view(generated, [&fileId](int num){ return num != fileId;});
            auto block_view = generated_until_index | std::views::enumerate | std::views::chunk_by([](auto a, auto b) {
                return std::get<1>(a) == std::get<1>(b);
            });
            for (auto block : block_view) {
                if (std::get<1>(*block.begin()) == -1) {
                    if (count <= block.size()) {
                        // fill fileId positions with -1
                        std::ranges::fill_n(generated.begin()+index, count, -1);
                        auto start = std::get<0>(*block.begin());
                        // fill -1s with fileId
                        std::ranges::fill_n(generated.begin() + start, count, fileId);
                        break;
                    }
                }
            }
        }
        return generated;
    }

    auto move_file_blocks_1(std::vector<int>&& generated) -> std::vector<int> {
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

    auto get_checksum(const std::string& input, const bool part2=false) -> u64 {
        const auto& processed = part2 ? move_file_blocks_2(generate_representation(input)) : move_file_blocks_1(
                generate_representation(input));
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
