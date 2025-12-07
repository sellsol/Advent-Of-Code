#include <iostream>
#include <fstream>

#include <string>
#include <cstdint>
#include <utility>
#include <algorithm>

int part1(std::string inputFile) {
    std::vector<std::pair<std::int64_t, std::int64_t>> idRanges;

    std::ifstream infile{inputFile};
    std::string line;
    while(getline(infile, line) && line != "") {
        size_t delimIndex{line.find('-')};
        idRanges.push_back({std::stoll(line.substr(0, delimIndex)), std::stoll(line.substr(delimIndex + 1))});
    }

    int numFresh{0};
    while(getline(infile, line)) {
        std::int64_t id{std::stoll(line)};
        for (std::pair<std::int64_t, std::int64_t> idRange : idRanges) {
            if (id >= idRange.first && id <= idRange.second) {
                numFresh++;
                break;
            }
        }
    }

    return numFresh;
}

std::int64_t part2(std::string inputFile) {
    std::vector<std::pair<std::int64_t, std::int64_t>> idRanges;

    std::ifstream infile{inputFile};
    std::string line;
    while(getline(infile, line) && line != "") {
        size_t delimIndex{line.find('-')};
        idRanges.push_back({std::stoll(line.substr(0, delimIndex)), std::stoll(line.substr(delimIndex + 1))});
    }

    std::sort(idRanges.begin(), idRanges.end());
    std::int64_t numAllFresh{0};
    std::int64_t prevRangeEnd{-1};
    for (std::pair<std::int64_t, std::int64_t> idRange : idRanges) {
        if (idRange.first > prevRangeEnd) {
            numAllFresh += idRange.second - idRange.first + 1;
            prevRangeEnd = idRange.second;
        } else if (idRange.first <= prevRangeEnd && idRange.second > prevRangeEnd) {
            numAllFresh += (idRange.second - (prevRangeEnd + 1) + 1);
            prevRangeEnd = idRange.second;
        }
    }

    return numAllFresh;
}

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;
    std::string inputFile{argv[1]};

    std::cout<< "Part 1 answer: " << part1(inputFile) << "\n";
    std::cout<< "Part 2 answer: " << part2(inputFile) << "\n";

    return 0;
}