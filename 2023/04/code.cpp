#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <sstream>
#include <set>

// String containing space separated numbers to a set of those numbers
std::set<int> numsStringToSet(std::string inputString) {
    std::set<int> nums;
    std::stringstream ss(inputString);
    int current;

    while(ss >> current) nums.insert(current);
    return nums;
}

// Count number of winning numbers from puzzle formatted string
int countWinningNums(std::string line) {
    size_t start = line.find(':');
    size_t splitter = line.find('|');

    std::set<int> winning(numsStringToSet(line.substr(start + 1, splitter)));
    std::set<int> ticket(numsStringToSet(line.substr(splitter + 1)));
    std::set<int> hits;
    std::set_intersection(winning.begin(), winning.end(), ticket.begin(), ticket.end(), inserter(hits, hits.begin()));

    return hits.size();
}

int part1(std::string inputFile) {
    int sum{0};

    std::string line;
    std::ifstream f(inputFile);
    while (getline(f, line)) {
        int winningCount{countWinningNums(line)};
        if (winningCount > 0) sum += 1 << (winningCount - 1);
    }

    return sum;
}

int part2(std::string inputFile) {
    std::vector<int> numCards(5, 1); // arbitrary initial size
    size_t lineIdx{0};
    int total{0};

    std::string line;
    std::ifstream f(inputFile);
    while (getline(f, line)) {
        if (lineIdx >= numCards.size()) numCards.push_back(1);
        int currentNumCards{numCards[lineIdx]};
        size_t winningCount{(size_t) countWinningNums(line)};

        if (lineIdx + winningCount >= numCards.size()) numCards.resize((lineIdx + winningCount) * 2, 1); // arbitrary doubling of size
        for (size_t i = lineIdx + 1; i < lineIdx + winningCount + 1; i++) {
            numCards[i] += currentNumCards;
        }

        total += currentNumCards;
        lineIdx++;
    }

    return total;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Wrong number of arguments: " << argc << std::endl;
        return 1;
    }
    std::string inputFile{argv[1]};

    std::cout << "Part 1 answer: " << part1(inputFile) << std::endl;
    std::cout << "Part 2 answer: " << part2(inputFile) << std::endl;
    return 0;
}