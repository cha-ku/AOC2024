//
// Created by chaku on 27/12/24.
//

#ifndef AOC2024_DAY12_HPP
#define AOC2024_DAY12_HPP

#include <unordered_map>
#include <deque>

namespace aoc::day12 {
    auto get_fencing_price(const std::vector<std::string>& orig_input)-> uint64_t {
        std::vector<std::string> input = orig_input;
        const auto num_rows = input.size();
        const auto num_cols = input[0].size();

        auto groups = [&](int r, int c) {
            std::deque<std::pair<int, int>> same_plants;
            std::vector<std::pair<int, int>> result;
            same_plants.emplace_back(r, c);
            while(!same_plants.empty()) {
                auto p = same_plants.back();
                r = p.first;
                c = p.second;
                if(r+1 < num_rows || r-1 >= 0 || c+1 < num_cols || c-1 >=0)  {
                    char plant = input[r][c];
                    if (plant == '.') {
                        same_plants.pop_back();
                        continue;
                    }
                    //std::cout << plant << " (" << r << " , " << c << ")\n";
                    result.emplace_back(same_plants.back());
                    same_plants.pop_back();
                    input[r][c] = '.';
                    if (c+1 < num_cols && input[r][c+1] == plant) {
                        same_plants.emplace_back(r, c+1);
                    }
                    if (r+1 < num_rows && input[r+1][c] == plant) {
                        same_plants.emplace_back(r+1, c);
                    }
                    if (c-1 >=0 && input[r][c-1] == plant) {
                        same_plants.emplace_back(r, c-1);
                    }
                    if (r-1 >= 0 && input[r-1][c] == plant) {
                        same_plants.emplace_back(r-1, c);
                    }
                }
            }
            return result;
        };

        uint64_t result{0};
        for(auto row = 0; row < num_rows; ++row) {
            for (auto col = 0; col < num_cols; ++col) {
                if (input[row][col] == '.') {
                    continue;
                }
                auto res = groups(row, col);
                uint64_t perimeter{0};
                for(const auto& [r, c] : res) {
                    std::vector<std::pair<int, int>> adjacent;
                    if (r+1 == num_rows) {
                        perimeter++;
                    }
                    else {
                        adjacent.emplace_back(1, 0);
                    }
                    if (r-1 < 0) {
                        perimeter++;
                    }
                    else {
                        adjacent.emplace_back(-1, 0);
                    }
                    if (c+1 == num_cols) {
                        perimeter++;
                    }
                    else {
                        adjacent.emplace_back(0, 1);
                    }
                    if (c-1 < 0) {
                        perimeter++;
                    }
                    else {
                        adjacent.emplace_back(0, -1);
                    }
                    perimeter +=
                            std::count_if(adjacent.begin(), adjacent.end(),
                                          [&](const std::pair<int, int>& pos){
                                const auto& [x, y] = pos;
                                return orig_input[r+x][c+y] != orig_input[r][c];
                            });
                }
                auto area = res.size();
                //std::cout << orig_input[row][col] << " " << area << " " << perimeter << "\n";
                result += area * perimeter;
            }
        }
        return result;
    }
}

#endif //AOC2024_DAY12_HPP
