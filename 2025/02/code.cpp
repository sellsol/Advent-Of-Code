#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdint>
#include <cmath>
#include <set>

int countDigits(std::int64_t num) {
    return num == 0 ? 1 : (int) std::log10(num) + 1;
}

std::string repeatString(std::string str, int times) {
    std::string repeatStr {str};
    for (int i = 1; i < times; i++) {
        repeatStr += str;
    }
    return repeatStr;
}

std::int64_t part1(std::string inputFile) {
    std::int64_t sum{0};

    std::ifstream infile{inputFile};
    std::stringstream ss;
    ss << infile.rdbuf();
    infile.close();

    std::string line;
    while (getline(ss, line, ',')) {
        size_t delim{line.find('-')};
        std::string start{line.substr(0, delim)};
        std::string end{line.substr(delim + 1)};

        // get first half of range start and range end values
        std::int64_t startHalf{0};
        std::int64_t endHalf{0};
        if (start.size() / 2 > 0) {
            startHalf = std::stoi(start.substr(0, start.size() / 2));
        }
        if (end.size() / 2 > 0) {
            endHalf = std::stoi(end.substr(0, (end.size() + 1) / 2));
        }

        // iterate between the halves and check if doubled pattern is in range
        for (std::int64_t i = startHalf; i <= endHalf; i++) {
            std::int64_t dupPattern{std::stoll(repeatString(std::to_string(i), 2))};

            if (dupPattern >= std::stoll(start) && dupPattern <= std::stoll(end)) {
                sum += dupPattern;
            }
        }
    }

    return sum;
}

std::int64_t part2(std::string inputFile) {
    std::int64_t sum{0};

    std::ifstream infile{inputFile};
    std::stringstream ss;
    ss << infile.rdbuf();
    infile.close();

    std::string line;
    while (getline(ss, line, ',')) {
        size_t delim{line.find('-')};
        std::string start{line.substr(0, delim)};
        std::string end{line.substr(delim + 1)};

        // get range end value
        std::int64_t endHalf{0};
        if (end.size() / 2 > 0) {
            endHalf = std::stoi(end.substr(0, (end.size() + 1) / 2));
        }

        // iterate up to the range end half double pattern and check all possible number of repeats
        std::set<int64_t> seen;
        for (std::int64_t i = 1; i <= endHalf; i++) {
            int numDigits{countDigits(i)};

            size_t minRepeats{start.size() / numDigits};
            size_t maxRepeats{end.size() / numDigits};
            for (size_t repeats = minRepeats; repeats <= maxRepeats; repeats++) {
                std::int64_t dupPattern{std::stoll(repeatString(std::to_string(i), repeats))};

                if (seen.count(dupPattern) == 0 && dupPattern >= std::stoll(start) && dupPattern <= std::stoll(end)) {
                    sum += dupPattern;
                    seen.insert(dupPattern);
                }
            }
        }
    }

    return sum;
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