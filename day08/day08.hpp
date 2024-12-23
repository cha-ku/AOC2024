//
// Created by chaku on 21/12/24.
//

#ifndef AOC2024_DAY08_HPP
#define AOC2024_DAY08_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <unordered_set>
#include <cmath>


namespace aoc::day08 {
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

    struct LocationPair {
        int r;
        int c;

        bool operator==(const LocationPair& other) const {
            return other.r == r and other.c == c;
        }
    };

    struct LocationPairHash {
        size_t operator()(const LocationPair& location) const
        {
            auto h1 = std::hash<int>{}(location.r);
            auto h2 = std::hash<int>{}(location.c);
            return h1 ^ (h2 << 1);
        }
    };
    using LocationPairSet = std::unordered_set<LocationPair, LocationPairHash>;
    using LocationPairVec = std::vector<LocationPair>;
    using AntennaLocationMap = std::unordered_map<char, LocationPairVec>;

    auto get_antenna_locations(const auto& input) -> AntennaLocationMap {
        const auto num_rows = input.size();
        const auto num_cols = input[0].size();
        AntennaLocationMap antennas;
        for (int r = 0; r < num_rows; ++r) {
            for (int c = 0; c < num_cols; ++c) {
                if (input[r][c] == '.') {
                    continue;
                }
                char antenna = input[r][c];
                if (antennas.contains(antenna)) {
                    antennas[antenna].emplace_back(LocationPair(r, c));
                    continue;
                }
                antennas[antenna] = {{r, c}};
            }
        }
        return antennas;
    }

    auto get_distance(const int pc, const int pr, const int ic, const int ir) {
        int distance{0};
        distance = std::abs(ic - pc)  + std::abs(ir - pr);
        return distance;
    }

    auto get_num_unique_locations(const auto& input, const bool only_two_antinodes=true) {
        LocationPairSet result;
        const auto& antenna_locations = get_antenna_locations(input);
        const auto num_rows = input.size();
        const auto num_cols = input[0].size();
        for (int r = 0; r < num_rows; ++r) {
            for (int c = 0; c < num_cols; ++c) {
                for (const auto& [key, value] : antenna_locations) {
                    for (int i = 0; i < value.size(); ++i) {
                        for (int j = i+1; j < value.size(); ++j) {
                            const auto& antenna1 = value[i];
                            const auto& antenna2 = value[j];

                            const auto distance_point_antenna1 = get_distance(c, r, antenna1.c, antenna1.r);
                            const auto distance_point_antenna2 = get_distance(c, r, antenna2.c, antenna2.r);

                            constexpr auto twice_distance = [](const double p_to_ant1, const double p_to_ant2) -> bool {
                                return (p_to_ant1 == 2 * p_to_ant2) or (p_to_ant2 == 2 * p_to_ant1);
                            };

                            const auto in_one_line = [&r, &c](const LocationPair& ant1, const LocationPair& ant2) -> bool {
                                return ((r - ant1.r) * (c - ant2.c)) == ((c - ant1.c) * (r - ant2.r));
                            };

                            if (only_two_antinodes)
                            {
                                if (in_one_line(antenna1, antenna2) and
                                    twice_distance(distance_point_antenna1,
                                                   distance_point_antenna2))
                                {
                                    result.emplace(LocationPair(r,c));
                                }
                                continue;
                            }

                            if (in_one_line(antenna1, antenna2))
                            {
                                result.emplace(LocationPair(r,c));
                            }
                        }
                    }
                }
            }
        }
        return result.size();
    }
}

#endif //AOC2024_DAY08_HPP
