#include <iostream>
#include <fstream>

using namespace std;

void part1(string inputFile) {
    int game = 0;
    bool gameValid = true;
    int sum = 0;

    char c;
    ifstream f(inputFile);
    while (f.get(c)) {
        if (!isdigit(c)) continue;

        int num = 0;
        while (isdigit(c)) {
            num = (num * 10) + (c - '0');
            f.get(c);
        }
        f.get(c);

        if (c == ' ') {
            if (gameValid) sum += game;
            game++;
            gameValid = true;
        }

        if ((c == 'r' && num > 12) ||
            (c == 'g' && num > 13) ||
            (c == 'b' && num > 14)
        ) {
            gameValid = false;
            f.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    if (gameValid) sum += game;
    f.close();

    cout << "Part 1 answer: " << sum << "\n";
}

void part2(string inputFile) {
    int blue = 0; int red = 0; int green = 0;
    int sum = 0;

    char c;
    ifstream f(inputFile);
    while (f.get(c)) {
        if (!isdigit(c)) continue;

        int num = 0;
        while (isdigit(c)) {
            num = (num * 10) + (c - '0');
            f.get(c);
        }
        f.get(c);

        if (c == ' ') {
            sum += blue * red * green;
            blue = 0; red = 0; green = 0;
        }

        if (c == 'r' && num > red) red = num;
        else if (c == 'g' && num > green) green = num;
        else if (c == 'b' && num > blue) blue = num;
    }
    sum += blue * red * green;
    f.close();

    cout << "Part 2 answer: " << sum << "\n";
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Wrong number of arguments: " << argc << "\n";
    }

    string inputFile = argv[1];

    part1(inputFile);
    part2(inputFile);
    return 0;
}