//
// Created by chaku on 01/01/25.
//

#include <cassert>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "day15.hpp"

auto test() -> int {
    std::vector<std::string> test_input1{
        "########",
        "#..O.O.#",
        "##@.O..#",
        "#...O..#",
        "#.#.O..#",
        "#...O..#",
        "#......#",
        "########"
    };
    const std::string directions{"<^^>>>vv<v>>v<<"};
    //assert(aoc::day15::sum_of_gps_coordinates(test_input1, directions) == 2028);

    std::vector<std::string> test_input2{
        "#######",
        "#...#.#",
        "#.....#",
        "#..OO@#",
        "#..O..#",
        "#.....#",
        "#######"
    };
    const std::string directions2{"<vv<<^^<<^^"};
    std::cout << aoc::day15::sum_of_gps_coordinates(test_input2, directions2, true) << "\n";

    std::vector<std::string> test_input3{
        "##########",
        "#..O..O.O#",
        "#......O.#",
        "#.OO..O.O#",
        "#..O@..O.#",
        "#O#..O...#",
        "#O..O..O.#",
        "#.OO.O.OO#",
        "#....O...#",
        "##########"
    };
    const std::string directions3{"<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^>^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^"};
    //assert(aoc::day15::sum_of_gps_coordinates(test_input3, directions3) == 10092);

    return 0;
}

auto parse_and_run(std::string_view path) -> int {
    std::vector<std::string> data;
    std::fstream file(static_cast<std::string>(path));
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(path) << "\n";
        return 1;
    }
    std::vector<std::string> grid;
    std::string line;
    bool is_grid = true;
    std::string move_sequence;
    while(std::getline(file, line)) {
        if (line.empty()) {
            is_grid = false;
        }
        if (is_grid) {
            grid.emplace_back(line);
        }
        else {
            move_sequence += line;
        }
    }
    std::cout << "Part 1 solution : " << aoc::day15::sum_of_gps_coordinates(grid, move_sequence) << "\n";
    //std::cout << "Part 2 solution : " << aoc::day14::check_easter_egg(input, 103, 101) << "\n";
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        return test();
    }
    else if (argc == 2) {
        return parse_and_run(argv[1]);
    }
    return 0;
}
