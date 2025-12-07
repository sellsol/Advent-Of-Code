#include <iostream>
#include <fstream>

#include <cstdint>
#include <string>
#include <vector>

int part1(std::string inputFile) {
    int numSplits{0};

    std::ifstream infile{inputFile};
    std::string line;

    getline(infile, line);
    std::vector<bool> beams(line.size(), false);
    beams[line.find("S")] = true;

    while (getline(infile, line)) {
        size_t splitterIndex{line.find("^")};
        while (splitterIndex != std::string::npos) {
            if (beams[splitterIndex]) {
                if (splitterIndex > 0) beams[splitterIndex - 1] = true;
                if (splitterIndex < beams.size() - 1) beams[splitterIndex + 1] = true;
                beams[splitterIndex] = false;
                numSplits++;
            }
            splitterIndex = line.find("^", splitterIndex + 1);
        }
    }

    return numSplits;
}

std::int64_t part2(std::string inputFile) {
    std::vector<std::string> lines;
    std::ifstream infile{inputFile};
    std::string line;
    while(getline(infile, line)) lines.push_back(line);

    std::vector<std::vector<std::int64_t>> dp(lines.size() - 1, std::vector<std::int64_t>(lines[0].size(), 0));
    dp.push_back(std::vector<int64_t>(lines[0].size(), 1));
    for (int depth = lines.size() - 2; depth >= 0; depth--) {
        for (int index = 0; index < (int) lines[0].size(); index++) {
            if (lines[depth][index] == '^') {
                dp[depth][index] = 0;
                if (index > 0) dp[depth][index] += dp[depth + 1][index - 1];
                if (index < (int) lines[0].size()) dp[depth][index] += dp[depth + 1][index + 1];
            } else {
                dp[depth][index] = dp[depth + 1][index];
            }
        }
    }

    return dp[0][lines[0].find("S")];
}

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;
    std::string inputFile{argv[1]};

    std::cout << "Part 1 answer: " << part1(inputFile) << "\n";
    std::cout << "Part 2 answer: " << part2(inputFile) << "\n";
}