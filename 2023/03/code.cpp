#include <iostream>
#include <fstream>

#include <map>
#include <set>

using namespace std;

struct Loc {
    int row; int col;
    bool operator<(const Loc& other) const {
        return row < other.row || (row == other.row && col < other.col);
    }
};
struct Part { int num; int id; };

map<Loc, Part> partNums;
vector<Loc> symLocs;
vector<Loc> gearLocs;

// Note that checks for indexes beyond number of rows and cols is unnecessary
// They will just never be associated with a number in the partNums map
vector<Loc> getNeighbourhood(Loc l) {
    vector<Loc> surroundingLocs;
    for (int i: {-1, 0, 1}) {
        for (int j: {-1, 0, 1}) {
            surroundingLocs.push_back(Loc{l.row + i, l.col + j});
        }
    }
    return surroundingLocs;
}

void parseFile(string inputFile) {
    string line;
    ifstream f(inputFile);

    int id = 0;
    int rowNum = 0;
    while(getline(f, line)) {
        int num = 0;

        for (int colNum = 0; colNum < static_cast<int>(line.size()); colNum++) {
            if (isdigit(line[colNum])) {
                num = (num * 10) + line[colNum] - '0';
            }
            if (!isdigit(line[colNum]) && line[colNum] != '.') {
                symLocs.push_back(Loc{rowNum, colNum});
            }
            if (line[colNum] == '*') {
                gearLocs.push_back(Loc{rowNum, colNum});
            }

            if (!isdigit(line[colNum]) && num != 0) {
                int numDigits = floor(log10(num)) + 1;
                for (int j = 0; j < numDigits; j++) {
                    partNums[Loc{rowNum, colNum - j - 1}] = {num, id};
                }
                id++;

                num = 0;
            }
        }

        if (num != 0) {
            int numDigits = floor(log10(num)) + 1;
            for (int j = 0; j < numDigits; j++) {
                partNums[Loc{rowNum, static_cast<int>(line.size()) - j - 1}] = {num, id};
            }
            id++;
        }

        rowNum++;
    }
    f.close();
}

int part1() {
    int sum = 0;
    for (Loc symLoc: symLocs) {
        set<int> seen;
        for (Loc neighbour: getNeighbourhood(symLoc)) {
            if (partNums[neighbour].num != 0 && !seen.count(partNums[neighbour].id)) {
                sum += partNums[neighbour].num;
                seen.insert(partNums[neighbour].id);
            }
        }
    }

    return sum;
}

int part2() {
    int sum = 0;
    for (Loc gearLoc: gearLocs) {
        set<int> seen;
        int gearSum = 1;
        for (Loc neighbour: getNeighbourhood(gearLoc)) {
            if (partNums[neighbour].num != 0 && !seen.count(partNums[neighbour].id)) {
                seen.insert(partNums[neighbour].id);
                gearSum *= partNums[neighbour].num;
            }
        }

        if (seen.size() == 2) {
            sum += gearSum;
        }
    }

    return sum;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Wrong number of arguments: " << argc;
        return 1;
    }

    string inputFile = argv[1];

    parseFile(inputFile);
    cout << "Part 1 answer: " << part1() << "\n";
    cout << "Part 2 answer: " << part2() << "\n";
    return 0;
}