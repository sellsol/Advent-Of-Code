#include <iostream>
#include <fstream>

#include <string>
#include <tuple>
#include <vector>
#include <queue>
#include <set>

#include <sstream>
#include <cstdint>
#include <cmath>
#include <algorithm>

struct DSU {
    std::vector<int> reps;
    std::vector<int> sizes;
    int distinct{0};

    DSU(int numElements) {
        for (int i = 0; i < numElements; i++) {
            reps.push_back(i);
            sizes.push_back(1);
        }
        distinct = numElements;
    }

    int findRep(int member) {
        if (reps[member] == member) return member;

        return reps[member] = findRep(reps[member]);
    }

    void unionSets(int memberA, int memberB) {
        int repA{findRep(memberA)};
        int repB{findRep(memberB)};
        if (repA != repB) {
            reps[repB] = repA;
            sizes[repA] += sizes[repB];
            sizes[repB] = 0;
            distinct--;
        }
    }
};

struct Dist {
    std::int64_t dist;
    int idA;
    int idB;

    bool operator<(const Dist& other) const {
        return dist > other.dist;
    }
};

std::int64_t getDistance3D(std::tuple<int, int, int> pointA, std::tuple<int, int, int> pointB) {
    double dx = std::abs(std::get<0>(pointA) - std::get<0>(pointB));
    double dy = std::abs(std::get<1>(pointA) - std::get<1>(pointB));
    double dz = std::abs(std::get<2>(pointA) - std::get<2>(pointB));
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

std::vector<std::tuple<int, int, int>> loadPoints(std::string inputFile) {
    std::vector<std::tuple<int, int, int>> points;

    std::ifstream infile{inputFile};
    std::string line;
    while (getline(infile, line)) {
        std::stringstream ss{line};
        int x, y, z;
        char comma;
        ss >> x >> comma >> y >> comma >> z;
        points.push_back({x, y, z});
    }

    return points;
}

std::int64_t part1(std::vector<std::tuple<int, int, int>>& points, int numConnections) {
    std::priority_queue<Dist> dists;
    for (int i = 0; i < (int) points.size(); i++) {
        for (int j = i + 1; j < (int) points.size(); j++) {
            std::int64_t dist = getDistance3D(points[i], points[j]);
            dists.push({dist, i, j});
        }
    }

    DSU dsu((int) points.size());
    for (int i = 0; i < numConnections; i++) {
        Dist shortestConn{dists.top()};
        dists.pop();

        dsu.unionSets(shortestConn.idA, shortestConn.idB);
    }

    std::vector<int>sortedSizes{dsu.sizes};
    std::sort(sortedSizes.begin(), sortedSizes.end(), std::greater<int>());

    return sortedSizes[0] * sortedSizes[1] * sortedSizes[2];
}

std::int64_t part2(std::vector<std::tuple<int, int, int>>& points) {
    std::priority_queue<Dist> dists;
    for (int i = 0; i < (int) points.size(); i++) {
        for (int j = i + 1; j < (int) points.size(); j++) {
            std::int64_t dist = getDistance3D(points[i], points[j]);
            dists.push({dist, i, j});
        }
    }

    DSU dsu((int) points.size());
    Dist shortestConn;
    while (dsu.distinct > 1) {
        shortestConn = dists.top();
        dists.pop();

        dsu.unionSets(shortestConn.idA, shortestConn.idB);
    }

    return std::get<0>(points[shortestConn.idA]) * std::get<0>(points[shortestConn.idB]);
}

int main(int argc, char* argv[]) {
    if (!(argc == 2 || argc == 3)) return 1;

    std::string inputFile{argv[1]};
    int numConnections{argc == 2 ? 1000 : std::stoi(argv[2])};

    std::vector<std::tuple<int, int, int>> points = loadPoints(inputFile);
    std::cout << "Part 1 answer: " << part1(points, numConnections) << "\n";
    std::cout << "Part 2 answer: " << part2(points) << "\n";

    return 0;
}