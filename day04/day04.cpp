#include <vector>
#include <cstdint>
#include <algorithm>
#include <cassert>
#include <iostream>

[[maybe_unused]] auto print = [](const auto& container) {
    std::for_each(container.cbegin(), container.cend(), [](const auto& elem) {
        std::cout << elem << ",";
    });
    std::cout << "\n";
};


auto column_wise = [](std::vector<std::string>& input_vec) {
    std::vector<std::string> all_combos;
    auto num_cols = input_vec[0].size();
    auto num_rows = input_vec.size();
    for(size_t col = 0; col < num_cols; ++col) {
        std::string column;
        for (size_t row = 0; row < num_rows; ++row) {
            column += input_vec[row][col];
        }
        all_combos.emplace_back(column);
    }
    return all_combos;
};

[[maybe_unused]] auto diagonal = [](std::vector<std::string>& input_vec) {
    std::vector<std::string> all_combos;
    auto num_cols = input_vec[0].size();
    auto num_rows = input_vec.size();
    size_t col = 0;
    while(col < num_cols) {
        size_t curr_col = col;
        size_t curr_row = 0;
        std::string diag;
        while(curr_col < num_cols && curr_row < num_rows) {
            //std::cout << "[" << curr_row << " , " << curr_col << "]" << "\n";
            diag += input_vec[curr_row][curr_col];
            curr_col++;
            curr_row++;
        }
        col++;
        //std::cout << diagonal << "\n";
        all_combos.emplace_back(diag);
    }

    // the rest of them
    // std::cout << "\nthe rest of them\n";
    size_t row = 1;
    while (row < num_rows) {
        size_t curr_row = row;
        size_t curr_col = 0;
        std::string diagonal;
        while(curr_row < num_rows && curr_col < num_cols) {
            //std::cout << "[" << curr_row << " , " << curr_col << "]" << "\n";
            diagonal += input_vec[curr_row][curr_col];
            curr_row++;
            curr_col++;
        }
        row++;
        //std::cout << diagonal << "\n";
        all_combos.emplace_back(diagonal);
    }
    return all_combos;
};

[[maybe_unused]] auto find_substr = [](std::vector<std::string>& sequences, const std::string& substr){
    uint64_t count{0};
    std::for_each(sequences.begin(), sequences.end(), [&](std::string& str) {
        size_t pos{0};
        while((pos = str.find(substr, pos)) != std::string::npos) {
            ++count;
            pos += substr.length();
        }
      });
    return count;
};

uint64_t get_count(const std::vector<std::string>& input) {
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

int main() {
    std::vector<std::string> test_input{
        {"MMMSXXMASM"},
        {"MSAMXMSMSA"},
        {"AMXSXMAAMM"},
        {"MSAMASMSMX"},
        {"XMASAMXAMM"},
        {"XXAMMXXAMA"},
        {"SMSMSASXSS"},
        {"SAXAMASAAA"},
        {"MAMMMXMMMM"},
        {"MXMXAXMASX"}};

    std::cout << get_count(test_input) << "\n";

    //auto all_rows = test_input;
    //std::cout << "rows - \n";
    //print(all_rows);
    //result += find_substr(all_rows, xmas);
    //result += find_substr(all_rows, samx);

    //std::vector<std::string> all_columns = column_wise(test_input);
    //std::cout << "columns - \n";
    //print(all_columns);
    //result += find_substr(all_columns, xmas);
    //result += find_substr(all_columns, samx);

    //std::vector<std::string> diagonals = diagonal(test_input);
    //std::cout << "diagonals - \n";
    //print(diagonals);
    //result += find_substr(diagonals, xmas);
    //result += find_substr(diagonals, samx);

    return 0;
}
