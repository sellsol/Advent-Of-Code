#include <iostream>
#include <fstream>
#include <cstdint>

#include <string>
#include <sstream>
#include <vector>
#include <cmath>

std::vector<std::int64_t> process_inputnums(std::string line) {
    std::vector<std::int64_t> nums;

    std::stringstream ss{line};
    std::string s;
    while (ss >> s) {
        nums.push_back(std::stoi(s));
    }

    return nums;
}

std::int64_t process_inputnum(std::string line) {
    std::string strnum;

    std::stringstream ss{line};
    std::string s;
    while (ss >> s) {
        strnum += s;
    }

    return std::stol(strnum);
}

std::int64_t calc_num_winning_times(std::int64_t time, std::int64_t distance) {
    // dist = (total_time - hold_time) * hold_time
    // dist = total_time*hold_time - hold_time^2
    // 0 = -h^2 + total_time*h - dist
    std::int64_t a{-1};
    std::int64_t b{time};
    std::int64_t c{-distance};

    // Get roots from quadratic formula
    std::int64_t root_neg{(std::int64_t) std::ceil((-b - std::sqrt(b * b - 4 * a * c)) / (2 * a))}; // always higher
    std::int64_t root_pos{(std::int64_t) std::floor((-b + std::sqrt(b * b - 4 * a * c)) / (2 * a))};

    return std::abs(root_neg - root_pos) - 1; // ceil and floor swapped - 1, to exclude for edge case where roots are round ints
}

std::int64_t part1(std::string inputFile) {
    // Input processing
    std::vector<std::int64_t> times, distances;

    std::ifstream infile{inputFile};
    std::string line;

    getline(infile, line);
    times = process_inputnums(line.substr(line.find(':') + 1));
    getline(infile, line);
    distances = process_inputnums(line.substr(line.find(':') + 1));

    // Calculations
    std::int64_t product{1};
    for (size_t i = 0; i < times.size(); i++) {
        product *= calc_num_winning_times(times[i], distances[i]);
    }

    return product;
}

std::int64_t part2(std::string inputFile) {
    std::ifstream infile{inputFile};
    std::string line;

    getline(infile, line);
    std::int64_t time {process_inputnum(line.substr(line.find(':') + 1))};
    getline(infile, line);
    std::int64_t dist {process_inputnum(line.substr(line.find(':') + 1))};

    return calc_num_winning_times(time, dist);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Wrong number of arguments: " << argc << std::endl;
        return 1;
    }
    std::string inputFile{argv[1]};

    std::cout<< "Part 1 answer: " << part1(inputFile) << "\n";
    std::cout<< "Part 2 answer: " << part2(inputFile) << "\n";

    return 0;
}