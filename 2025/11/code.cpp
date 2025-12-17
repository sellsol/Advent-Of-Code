#include <iostream>
#include <fstream>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <map>
#include <queue>
#include <tuple>
#include <set>

std::map<std::string, std::vector<std::string>> edges;

void loadEdges(std::string inputFile) {
    std::ifstream infile{inputFile};
    std::string line;
    while (getline(infile, line)) {
        size_t delimIndex{line.find(":")};
        std::string source{line.substr(0, delimIndex)};

        std::stringstream ss{line.substr(delimIndex + 1)};
        std::string target;
        while (ss >> target) {
            if (edges.find(source) != edges.end()) {
                edges.insert({source, std::vector<std::string>{}});
            }
            edges[source].push_back(target);
            if (edges.find(target) != edges.end()) {
                edges.insert({target, std::vector<std::string>{}});
            }
        }
    }
}

int part1() {
    int numPossibilities{0};
    std::queue<std::string> paths{{"you"}};
    while (!paths.empty()) {
        std::string current{paths.front()}; paths.pop();

        if (current == "out") {
            numPossibilities++;
            continue;
        }

        for (std::string neighbour : edges[current]) {
            paths.push(neighbour);
        }
    }

    return numPossibilities;
}

long part2() {
    // Topological sort
    std::map<std::string, int> indegrees;
    for (auto [source, targets]: edges) {
        if (!indegrees.count(source)) indegrees[source] = 0;
        for (std::string target : targets) {
            indegrees[target]++;
        }
    }

    std::vector<std::string> sortedNodes;
    std::queue<std::string> q;
    for (auto [target, indegree]: indegrees) {
        if (indegree == 0) q.push(target);
    }

    while (!q.empty()) {
        std::string current{q.front()}; q.pop();
        sortedNodes.push_back(current);

        for (std::string target : edges[current]) {
            indegrees[target]--;
            if (indegrees[target] == 0) q.push(target);
        }
    }

    // Iterating in reverse topological order, numPossibilities(source) = Sumall numPossibilities(target)
    std::map<std::string, std::array<long, 4>> numPaths{{"out", {0, 0, 0, 1}}}; // node, num valid, num w/o dac, num w/o fft, num w/o both
    for (int i = sortedNodes.size() - 2; i >= 0; i--) {
        std::string current{sortedNodes[i]};

        numPaths[current] = {0, 0, 0, 0};
        for (std::string target : edges[sortedNodes[i]]) {
            auto [valid, onlyFft, onlyDac, neither]{numPaths[target]};

            if (current == "fft") {
                numPaths[current][0] += valid + onlyDac;
                numPaths[current][1] += onlyFft + neither;
            } else if (current == "dac") {
                numPaths[current][0] += valid + onlyFft;
                numPaths[current][2] += onlyDac + neither;
            } else {
                numPaths[current][0] += valid;
                numPaths[current][1] += onlyFft;
                numPaths[current][2] += onlyDac;
                numPaths[current][3] += neither;
            }
        }

        if (current == "svr") return numPaths[current][0];
    }

    return -1;
}

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;
    std::string inputFile{argv[1]};

    loadEdges(inputFile);
    std::cout<< "Part 1 answer: " << part1() << "\n";
    std::cout<< "Part 2 answer: " << part2() << "\n";

    return 0;
}