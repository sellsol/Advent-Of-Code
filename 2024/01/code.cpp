#include <iostream>
#include <fstream>

#include <sstream>
#include <cmath>
#include <map>

using namespace std;

vector<int> list_1;
vector<int> list_2;
map<int, int> map_2;

vector<string> splitString(string input) {
    vector<string> tokens;
    stringstream stream(input);
    string token;

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

void parseFile(string inputFile) {
    string line;
    ifstream f(inputFile);
    while (getline(f, line)) {
        vector<string> nums = splitString(line);

        list_1.push_back(stoi(nums[0]));
        list_2.push_back(stoi(nums[1]));

        map_2[stoi(nums[1])] += 1;
    }

    f.close();
}

int part1() {
    sort(list_1.begin(), list_1.end());
    sort(list_2.begin(), list_2.end());

    int sum = 0;
    for (size_t i = 0; i < list_1.size(); i++) {
        sum += abs(list_1[i] - list_2[i]);
    }

    return sum;
}

int part2() {
    int sum = 0;
    for (size_t i = 0; i < list_1.size(); i++) {
        sum += list_1[i] * map_2[list_1[i]];
    }

    return sum;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Wrong number of arguments: " << argc << "\n";
        return 1;
    }
    string inputFile = argv[1];

    parseFile(inputFile);
    cout << "Part 1 answer: " << part1() << "\n";
    cout << "Part 2 answer: " << part2() << "\n";
    return 0;
}