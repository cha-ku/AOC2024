//
// Created by chaku on 09/12/24.
//

#ifndef AOC2024_DAY04_HPP
#define AOC2024_DAY04_HPP

#include <vector>
#include <cstdint>
#include <algorithm>
#include <cassert>
#include <iostream>

namespace aoc::day04 {
    uint64_t get_xmas_count(const std::vector<std::string>& input) {
        uint64_t result{0};
        const int num_cols = input[0].size();
        const int num_rows = input.size();
        for(int row = 0; row < num_rows; ++row) {
            for(int col = 0; col < num_cols; ++col) {
                if (input[row][col] == 'X') {
                    // check in row to the right - X M A S
                    if (col+3 < num_cols) {
                        if (input[row][col+1] == 'M' and input[row][col+2] == 'A' and input[row][col+3] == 'S') {
                            result++;
                        }
                    }
                    // check in row to the left - S A M X
                    if (col-3 >= 0) {
                        if (input[row][col-1] == 'M' and input[row][col-2] == 'A' and input[row][col-3] == 'S') {
                            result++;
                        }
                    }
                    // check in column to down - X
                    //                           M
                    //                           A
                    //                           S
                    if (row+3 < num_rows) {
                        if (input[row+1][col] == 'M' and input[row+2][col] == 'A' and input[row+3][col] == 'S') {
                            result++;
                        }
                    }
                    //                           S
                    //                           A
                    //                           M
                    // check in column to down - X
                    if (row-3 >= 0) {
                        if (input[row-1][col] == 'M' and input[row-2][col] == 'A' and input[row-3][col] == 'S') {
                            result++;
                        }
                    }
                    // check in diagonal to the right and down - X
                    //                                             M
                    //                                               A
                    //                                                 S
                    if (row+3 < num_rows and col+3 < num_cols) {
                        if (input[row+1][col+1] == 'M' and input[row+2][col+2] == 'A' and input[row+3][col+3] == 'S') {
                            result++;
                        }
                    }
                    //                                               S
                    //                                             A
                    //                                           M
                    // check in diagonal to the right and up - X
                    if (row-3 >= 0 and col+3 < num_cols) {
                        if (input[row-1][col+1] == 'M' and input[row-2][col+2] == 'A' and input[row-3][col+3] == 'S') {
                            result++;
                        }
                    }
                    // check in diagonal to the left and down - X
                    //                                        M
                    //                                      A
                    //                                    S
                    if (row+3 < num_rows and col-3 >= 0) {
                        if (input[row+1][col-1] == 'M' and input[row+2][col-2] == 'A' and input[row+3][col-3] == 'S') {
                            result++;
                        }
                    }
                    //                                  S
                    //                                    A
                    //                                      M
                    // check in diagonal to the left and up - X
                    if (row-3 >= 0 and col-3 >= 0) {
                        if (input[row-1][col-1] == 'M' and input[row-2][col-2] == 'A' and input[row-3][col-3] == 'S') {
                            result++;
                        }
                    }
                }
            }
        }
        return result;
    }

    uint64_t get_x_mas_count(const std::vector<std::string>& input) {
        uint64_t result{0};
        const int num_cols = input[0].size();
        const int num_rows = input.size();
        for(int row = 0; row < num_rows; ++row) {
            for(int col = 0; col < num_cols; ++col) {
                if (input[row][col] == 'A') {
                    //(1)
                    //                                    M
                    // check in diagonal to the right  -    A
                    //                                        S
                    //(2)
                    //              OR
                    //                                    S
                    // check in diagonal to the right -     A
                    //                                        M
                    //
                    //             AND
                    //(3)
                    //
                    //                                       M
                    // check in diagonal to the left  -    A
                    //                                   S
                    //              OR
                    //(4)
                    //                                       S
                    // check in diagonal to the left  -    A
                    //                                   M
                    if (row+1 < num_rows and row-1 >= 0 and col+1 < num_cols and col-1 >= 0) {
                        if (
                            //(1)
                            ((input[row-1][col-1] == 'M' and input[row+1][col+1] == 'S') or
                            //(2)
                            (input[row-1][col-1] == 'S' and input[row+1][col+1] == 'M'))
                            and 
                            //(3)
                            ((input[row-1][col+1] == 'M' and input[row+1][col-1] == 'S') or
                            //(4)
                            (input[row-1][col+1] == 'S' and input[row+1][col-1] == 'M'))
                            )
                        {
                            result++;
                        }
                    }
                }
            }
        }
        return result;
    }

    [[maybe_unused]] auto print = [](const auto& container) {
        std::for_each(container.cbegin(), container.cend(), [](const auto& elem) {
                std::cout << elem << ",";
        });
        std::cout << "\n";
    };
}

#endif //AOC2024_DAY04_HPP
