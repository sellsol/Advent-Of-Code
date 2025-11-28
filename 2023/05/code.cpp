#include <iostream>
#include <fstream>

#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <set>

struct gardenMap {
    long targetStart;
    long sourceStart;
    long range;

    long sourceToTarget(long seedVal) {
        if (seedVal < sourceStart || seedVal > sourceStart + range - 1) return -1;

        return targetStart + (seedVal - sourceStart);
    }

    std::vector<std::pair<long, long>> sourceSegment(long seedStart, long seedRange) {
        long sourceEnd{sourceStart + range - 1};
        long seedEnd{seedStart + seedRange - 1};
        std::vector<std::pair<long, long>> seedRanges;

        if (seedEnd < sourceStart || seedStart > sourceEnd) return seedRanges;

        if (seedStart < sourceStart) {
            seedRanges.push_back(std::pair<long, long> (seedStart, sourceStart - seedStart));
            seedStart = sourceStart;
        }
        if (seedEnd > sourceEnd) {
            seedRanges.push_back(std::pair<long, long> (sourceEnd + 1, seedEnd - sourceEnd));
            seedEnd = sourceEnd;
        }
        seedRanges.push_back(std::pair<long, long> (seedStart, seedEnd - seedStart + 1));
        return seedRanges;
    }
};

long part1(std::string inputFile) {
    std::ifstream f(inputFile);

    // Input processing - seeds
    std::string line;
    getline(f, line);
    std::stringstream ssFirst(line.substr(line.find(':') + 1));

    long current;
    std::vector<long> currentSeeds;
    while(ssFirst >> current) {
        currentSeeds.push_back(current);
    }

    getline(f, line); getline(f, line); // skip

    // Input processing - maps
    for (int mapIdx = 0; mapIdx < 7; mapIdx++) {
        std::set<long> notSeen(currentSeeds.begin(), currentSeeds.end());
        std::vector<long> mappedSeeds;

        while(getline(f, line) && line != "") {
            std::stringstream ss(line);
            long targetStart, sourceStart, range;
            ss >> targetStart >> sourceStart >> range;

            gardenMap gMap = {targetStart, sourceStart, range};

            for (size_t i = 0; i < currentSeeds.size(); i++) {
                long seed{currentSeeds[i]};
                long mapped{gMap.sourceToTarget(seed)};

                if (mapped != -1) {
                    mappedSeeds.push_back(mapped);
                    notSeen.erase(seed);
                }
            }
        }

        for (long seed : notSeen) {
            mappedSeeds.push_back(seed);
        }

        currentSeeds = mappedSeeds;
        getline(f, line); // skip
    }

    // Lowest final location
    return *std::min_element(currentSeeds.begin(), currentSeeds.end());
}

long part2(std::string inputFile) {
    std::ifstream f(inputFile);

    // Input processing - seeds
    std::string line;
    getline(f, line);
    std::stringstream ssFirst(line.substr(line.find(':') + 1));

    long current; long currentRange;
    std::vector<std::pair<long, long>> currentRanges;
    while(ssFirst >> current) {
        ssFirst >> currentRange;
        currentRanges.push_back(std::pair<long, long> (current, currentRange));
    }

    getline(f, line); getline(f, line); // skip

    // Input processing - maps
    for (int mapIdx = 0; mapIdx < 7; mapIdx++) {
        std::set<long> seen;
        std::vector<std::pair<long, long>> mappedRanges;

        while(getline(f, line) && line != "") {
            std::stringstream ss(line);
            long targetStart; long sourceStart; long range;
            ss >> targetStart >> sourceStart >> range;

            gardenMap gMap = {targetStart, sourceStart, range};

            for (size_t i = 0; i < currentRanges.size(); i++) {
                long seed {currentRanges[i].first}, seedRange {currentRanges[i].second};
                std::vector<std::pair<long, long>> segments {gMap.sourceSegment(seed, seedRange)};

                if (segments.empty()) continue;

                for (size_t i = 0; i < segments.size(); i++) {
                    if (seen.count(segments[i].first) > 0) {
                        continue;
                    } else if (i >= segments.size() - 1) {
                        mappedRanges.push_back(std::pair<long, long> {gMap.sourceToTarget(segments[i].first), segments[i].second});
                        seen.insert(segments[i].first);
                    } else {
                        currentRanges.push_back(segments[i]);
                    }
                }
            }
        }

        for (std::pair<long, long> range : currentRanges) {
            if (seen.count(range.first) == 0) mappedRanges.push_back(range);
        }

        currentRanges = mappedRanges;
        getline(f, line); // skip
    }

    // Lowest final location
    long minLoc = currentRanges[0].first;
    for (std::pair<long, long> range : currentRanges) {
        if (range.first < minLoc) minLoc = range.first;
    }

    return minLoc;
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