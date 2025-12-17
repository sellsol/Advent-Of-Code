#include <iostream>
#include <fstream>

#include <string>
#include <sstream>
#include <queue>

std::vector<bool> xorBoolVecs(std::vector<bool> bitsA, std::vector<bool> bitsB) {
    for (int i = 0; i < (int) bitsA.size(); i++) {
        bitsA[i] = bitsA[i] ^ bitsB[i];
    }
    return bitsA;
}

int part1(std::string inputFile) {
    int totalPresses{0};

    std::ifstream infile{inputFile};
    std::string line;
    while (getline(infile, line)) {
        size_t delimIndex{line.find("]")};
        std::vector<bool> targetLights;
        for (char light : line.substr(1, delimIndex - 1)) {
            targetLights.push_back(light == '#' ? true : false);
        }

        std::vector<std::vector<bool>> buttons;
        std::stringstream lineSS{line.substr(delimIndex + 1)};
        std::string lineSplitStr;
        while (lineSS >> lineSplitStr && lineSplitStr[0] != '{') {
            buttons.push_back(std::vector<bool>(targetLights.size(), false));
            std::stringstream lineSplitSS{lineSplitStr.substr(1, lineSplitStr.size() - 2)};
            std::string numStr;
            while (getline(lineSplitSS, numStr, ',')) {
                buttons[buttons.size() - 1][std::stoi(numStr)] = true;
            }
        }

        // unique combinations of all lengths as a tree
        std::queue<std::vector<int>> combosQueue;
        for (int i = 0; i < (int) buttons.size(); i++) combosQueue.push({i});
        while (!combosQueue.empty()) {
            std::vector<int> combo{combosQueue.front()}; combosQueue.pop();
            std::vector<bool> comboLights(targetLights.size(), false);
            for (int buttonIndex : combo) {
                comboLights = xorBoolVecs(comboLights, buttons[buttonIndex]);
            }

            if (comboLights == targetLights) {
                totalPresses += combo.size();
                break;
            }

            for (int next = combo.back() + 1; next < (int) buttons.size(); next++) {
                std::vector<int> newCombo{combo};
                newCombo.push_back(next);
                combosQueue.push(newCombo);
            }
        }
    }

    return totalPresses;
}

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;
    std::string inputFile(argv[1]);

    std::cout<< "Part 1 answer: " << part1(inputFile) << "\n";
    // Not done: Part 2

    return 0;
}
