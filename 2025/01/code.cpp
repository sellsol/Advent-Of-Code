#include <iostream>
#include <fstream>

#include <string>
#include <cmath>

int part1(std::string inputFile) {
    int current{50};
    int numZeros{0};

    std::ifstream infile{inputFile};
    std::string instruction;
    while (getline(infile, instruction)) {
        if (instruction[0] == 'L') {
            current = ((current - std::stoi(instruction.substr(1))) % 100 + 100) % 100; // positive modulo
        } else { // instruction[0] == 'R'
            current = (current + std::stoi(instruction.substr(1))) % 100;
        }

        if (current == 0) numZeros++;
    }

    return numZeros;
}

int part2(std::string inputFile) {
    int current{50};
    int numZeros{0};

    std::ifstream infile{inputFile};
    std::string instruction;
    while (getline(infile, instruction)) {
        if (instruction[0] == 'L') {
            int original{current};
            current -= std::stoi(instruction.substr(1));

            if (original > 0 && current < 0) numZeros++;
        } else {
            current += std::stoi(instruction.substr(1));
        }

        if (current == 0) numZeros++;
        numZeros += std::abs(current / 100);

        current = (current % 100 + 100) % 100; // positive modulo
        // std::cout << current << "\n";
    }

    return numZeros;
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