#include <iostream>
#include <fstream>

#include <cstdint>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

std::int64_t part1(std::string inputFile) {
    std::vector<std::vector<std::int64_t>> lines;

    std::ifstream infile{inputFile};
    std::string line;
    while (getline(infile, line)) {
        std::stringstream ss{line};
        std::string num;

        std::vector<std::int64_t> line;
        while(ss >> num) {
            if (!std::isdigit(num[0])) break;
            line.push_back(std::stoll(num));
        }
        if (std::isdigit(num[0])) lines.push_back(line);
    }

    std::int64_t sumAll{0};

    std::stringstream ss{line};
    std::string op;
    int colsIndex{0};
    while (ss >> op) {
        std::int64_t total{0};
        if (op == "*") {
            total = 1;
            for (size_t rowIndex = 0; rowIndex < lines.size(); rowIndex++) total *= lines[rowIndex][colsIndex];
        } else {
            for (size_t rowIndex = 0; rowIndex < lines.size(); rowIndex++) total += lines[rowIndex][colsIndex];
        }
        sumAll += total;
        colsIndex++;
    }

    return sumAll;
}

std::int64_t part2(std::string inputFile) {
    std::vector<std::string> lines;
    size_t maxLineSize{0};

    std::ifstream infile{inputFile};
    std::string line;
    while (getline(infile, line)) {
        lines.push_back(line);
        if (line.size() > maxLineSize) maxLineSize = line.size();
    }

    std::string operators{lines.back()};
    lines.pop_back();

    std::int64_t sumAll{0};
    std::vector<std::int64_t> currentNums;
    for (int colIndex = maxLineSize - 1; colIndex >= 0; colIndex--) {
        std::string currentNumStr;
        for (size_t rowIndex = 0; rowIndex < lines.size(); rowIndex++) {
            if (colIndex >= (int) lines[rowIndex].size()) continue;

            char digit{lines[rowIndex][colIndex]};
            if (digit != ' ') currentNumStr.push_back(digit);
        }
        currentNums.push_back(std::stoll(currentNumStr));

        if (colIndex < (int) operators.size() && operators[colIndex] != ' ') {
            std::int64_t total{0};
            if (operators[colIndex] == '*') {
                total = 1;
                for (std::int64_t num : currentNums) total *= num;
            } else if (operators[colIndex] == '+') {
                for (std::int64_t num : currentNums) total += num;
            }

            sumAll += total;
            currentNums.clear();
            colIndex--; // skip blank column
        }
    }

    return sumAll;
}

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;
    std::string inputFile{argv[1]};

    std::cout<< "Part 1 answer: " << part1(inputFile) << "\n";
    std::cout<< "Part 2 answer: " << part2(inputFile) << "\n";

    return 0;
}