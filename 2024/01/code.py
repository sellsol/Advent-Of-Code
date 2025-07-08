import sys

from collections import Counter

list_1 = []
list_2 = []

def parse_file(input_path: str):
    with open(input_path) as f:
        for line in f:
            num_1, num_2 = line.split()
            list_1.append(int(num_1))
            list_2.append(int(num_2))

def part_1():
    sum = 0

    list_1.sort()
    list_2.sort()
    for a, b in zip(list_1, list_2):
        sum += abs(a - b)

    print(f"Part 1 answer: {sum}")

def part_2():
    sum = 0

    counter_2 = Counter(list_2)
    for num in list_1:
        sum += num * counter_2.get(num, 0)

    print(f"Part 2 answer: {sum}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Wrong number of arguments: {len(sys.argv)}")
        sys.exit(1)
    input_path = sys.argv[1]

    parse_file(input_path)
    part_1()
    part_2()
