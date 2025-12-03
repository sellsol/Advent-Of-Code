#include <iostream>
#include <fstream>

#include <cstdint>
#include <string>
#include <algorithm>
#include <iterator>

size_t getMaxElementIndex(std::string str, size_t startIndex, size_t endIndex) {
    size_t maxIndex{startIndex};
    for (size_t i = startIndex + 1; i <= endIndex; i++) {
        if (str[i] > str[maxIndex]) maxIndex = i;
    }
    return maxIndex;
}

std::int64_t countMaxJoltages(std::string inputFile, int numBatteriesOn) {
    std::int64_t sum{0};

    std::ifstream infile{inputFile};
    std::string line;
    while (getline(infile, line)) {
        std::string maxStr;
        size_t maxPrevIndex{0};

        for (int i = 0; i < numBatteriesOn; i++) {
            size_t maxIndex = getMaxElementIndex(line, maxPrevIndex, (line.size() - 1) - (numBatteriesOn - 1 - i));
            maxStr.push_back(line[maxIndex]);
            line.erase(maxIndex, 1);

            maxPrevIndex = maxIndex;
        }

        sum += std::stoll(maxStr);
    }

    return sum;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Wrong number of arguments: " << argc << std::endl;
        return 1;
    }
    std::string inputFile{argv[1]};

    std::cout<< "Part 1 answer: " << countMaxJoltages(inputFile, 2) << "\n";
    std::cout<< "Part 2 answer: " << countMaxJoltages(inputFile, 12) << "\n";

    return 0;
}