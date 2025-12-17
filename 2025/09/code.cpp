#include <iostream>
#include <fstream>
#include <cstdint>
#include <utility>

#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <queue>

std::vector<std::pair<long, long>> coords;
std::vector<std::pair<long, long>> coordsCompressed;
std::vector<long> xVec;
std::vector<long> yVec;
std::map<long, long> compressX;
std::map<long, long> compressY;

std::pair<long, long> compressCoords(std::pair<long, long> coordPair) {
    return {compressX[coordPair.first] * 2 + 1, compressY[coordPair.second] * 2 + 1}; // adds boundary 0s for flood fill
}

void loadCoords(std::string inputFile) {
    std::set<long> xSet;
    std::set<long> ySet;

    std::ifstream infile{inputFile};
    std::string line;
    while (getline(infile, line)) {
        std::stringstream ss{line};
        int left, right;
        char comma;
        ss >> left >> comma >> right;
        coords.push_back({left, right});

        xSet.insert(left);
        ySet.insert(right);
    }

    // Coordinate compression for part 2
    xVec = std::vector<long>(xSet.begin(), xSet.end()); // sets are sorted by default
    yVec = std::vector<long>(ySet.begin(), ySet.end());

    for (size_t i = 0; i < xVec.size(); i++) compressX[xVec[i]] = i;
    for (size_t i = 0; i < yVec.size(); i++) compressY[yVec[i]] = i;

    for (std::pair<long, long> coord : coords) {
        coordsCompressed.push_back(compressCoords(coord));
    }
}

long calcArea(std::pair<long, long> pointA, std::pair<long, long> pointB) {
    return ((std::abs(pointA.first - pointB.first) + 1) * (std::abs(pointA.second - pointB.second) + 1));
}

long part1() {
    long maxArea{0};
    for (size_t i = 0; i < coords.size(); i++) {
        for (size_t j = i + 1; j < coords.size(); j++) {
            long area{calcArea(coords[i], coords[j])};
            if (area > maxArea) maxArea = area;
        }
    }

    return maxArea;
}

enum TILE { IN, OUT, UNKNOWN };
std::pair<int, int> DIRECTIONS[] {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

long part2() {
    std::vector<std::vector<TILE>> grid(compressX.size() * 2 + 1, std::vector<TILE>(compressY.size() * 2 + 1, TILE::UNKNOWN));
    coordsCompressed.push_back(coordsCompressed[0]);

    // mark shape boundary on grid with compressed coordinates
    std::pair<long, long> prev = coordsCompressed[0];
    grid[prev.first][prev.second] = TILE::IN;
    for (size_t i = 1; i < coordsCompressed.size(); i++) {
        std::pair<long, long> current = coordsCompressed[i];

        if (prev.first == current.first) { // vertical
            for (long j = std::min(prev.second, current.second); j < std::max(prev.second, current.second); j++) {
                grid[prev.first][j] = TILE::IN;
            }
        } else { // horizontal
            for (long j = std::min(prev.first, current.first); j < std::max(prev.first, current.first); j++) {
                grid[j][prev.second] = TILE::IN;
            }
        }
        prev = current;
    }
    coordsCompressed.pop_back();

    // flood fill outside
    std::queue<std::pair<long, long>> q;
    q.push({0, 0});

    while (!q.empty()) {
        std::pair<long, long> current{q.front()}; q.pop();

        for (std::pair<int, int> dir : DIRECTIONS) {
            std::pair<long, long> neighbour{current.first + dir.first, current.second + dir.second};
            if (neighbour.first >= 0 && neighbour.first < (long) grid.size()
            && neighbour.second >= 0 && neighbour.second < (long) grid[0].size()
            && grid[neighbour.first][neighbour.second] == TILE::UNKNOWN) {
                grid[neighbour.first][neighbour.second] = TILE::OUT;
                q.push(neighbour);
            }
        }
    } // all UNKNOWNs henceforth can be treated as INs

    // check perimeters of possible squares for valid areas
    long maxArea{0};
    for (size_t i = 0; i < coordsCompressed.size(); i++) {
        for (size_t j = i + 1; j < coordsCompressed.size(); j++) {
            long minX = std::min(coordsCompressed[i].first, coordsCompressed[j].first);
            long maxX = std::max(coordsCompressed[i].first, coordsCompressed[j].first);
            long minY = std::min(coordsCompressed[i].second, coordsCompressed[j].second);
            long maxY = std::max(coordsCompressed[i].second, coordsCompressed[j].second);

            bool perimeterValid{true};
            for (long x = minX; x <= maxX; x++) {
                if (grid[x][minY] == TILE::OUT || grid[x][maxY] == TILE::OUT) {
                    perimeterValid = false;
                    break;
                }
            }
            if (!perimeterValid) continue;
            for (long y = minY; y <= maxY; y++) {
                if (grid[minX][y] == TILE::OUT || grid[maxX][y] == TILE::OUT) {
                    perimeterValid = false;
                    break;
                }
            }
            if (!perimeterValid) continue;

            long area{calcArea(coords[i], coords[j])};
            if (area > maxArea) maxArea = area;
        }
    }

    return maxArea;
}

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;

    std::string inputFile{argv[1]};

    loadCoords(inputFile);
    std::cout << "Part 1 answer: " << part1() << "\n";
    std::cout << "Part 2 answer: " << part2() << "\n";

    return 0;
}