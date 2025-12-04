#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <utility>

std::pair<int, int> DIRECTIONS[] {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1}, {0, 1},
    {1, -1}, {1, 0}, {1, 1}
};
std::vector<std::string> GRID;

void load_grid(std::string inputFile) {
    std::ifstream infile{inputFile};
    std::string line;
    while (getline(infile, line)) GRID.push_back(line);
}

int removeRolls(bool replace) {
    int numRemoved{0};
    std::vector<std::string> newGrid{GRID};

    for (size_t row = 0; row < GRID.size(); row++) {
        for (size_t col = 0; col < GRID[0].size(); col++) {
            if (GRID[row][col] == '.') {
                newGrid[row][col] = '.';
                continue;
            }

            int numNeighbourRolls{0};
            for (std::pair<int, int> direction : DIRECTIONS) {
                size_t neighbourRow{row + direction.first};
                size_t neighbourCol{col + direction.second};

                if (neighbourRow >= 0 && neighbourRow < GRID.size()
                && neighbourCol >= 0 && neighbourCol < GRID[0].size()
                && GRID[neighbourRow][neighbourCol] == '@') {
                    numNeighbourRolls++;
                }
            }

            if (numNeighbourRolls < 4) {
                newGrid[row][col] = '.';
                numRemoved++;
            } else {
                newGrid[row][col] = '@';
            }
        }
    }

    if (replace) GRID = newGrid;
    return numRemoved;
}

int removeRepeated() {
    int totalNumRemoved{0};

    int numRemoved = removeRolls(true);
    while (numRemoved != 0) {
        totalNumRemoved += numRemoved;
        numRemoved = removeRolls(true);
    }
    return totalNumRemoved;
}

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;
    std::string inputFile{argv[1]};

    load_grid(inputFile);
    std::cout<< "Part 1 answer: " << removeRolls(false) << "\n";
    std::cout<< "Part 2 answer: " << removeRepeated() << "\n";

    return 0;
}