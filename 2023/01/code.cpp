#include <iostream>
#include <fstream>

using namespace std;

void part1(string inputFile) {
    int sum = 0;

    string line;
    ifstream f(inputFile);
    while (getline(f, line)) {
        int calVal = 0;
        for (size_t i = 0; i < line.size(); i++) {
            if (isdigit(line[i])) {
                calVal += (line[i] - '0') * 10;
                break;
            }
        }
        for (size_t i = line.size() - 1; i >= 0; i--) {
            if (isdigit(line[i])) {
                calVal += line[i] - '0';
                break;
            }
        }

        sum += calVal;
    }
    f.close();

    cout << "Part 1 answer: " << sum << "\n";
}

void part2(string inputFile) {
    string numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int sum = 0;

    string line;
    ifstream f(inputFile);
    while (getline(f, line)) {
        vector<int> digits;
        for (size_t i = 0; i < line.size(); i++) {
            if (isdigit(line[i])) {
                digits.push_back(line[i] - '0');
                continue;
            }

            for (int j = 0; j < 9; j++) {
                int start_idx = i - numbers[j].size() + 1;
                if (start_idx < 0) continue;
                if (line.substr(start_idx, numbers[j].size()) == numbers[j]) {
                    digits.push_back(j + 1);
                    break;
                }
            }
        }

        sum += digits[0] * 10 + digits.back();
    }
    f.close();

    cout << "Part 2 answer: " << sum << "\n";
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Wrong number of arguments: " << argc << "\n";
        return 1;
    }
    string inputFile = argv[1];

    part1(inputFile);
    part2(inputFile);
    return 0;
}