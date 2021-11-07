
from Helper.helper import measure_time
import argparse
import os

DEFAULT_INPUT = os.path.join(os.path.dirname(__file__), 'input.txt')


def compute(s: str) -> int:
    possibilities = set(range(1024))

    for line in s.splitlines():
        line = line.replace('F', '0').replace('B', '1')
        line = line.replace('R', '1').replace('L', '0')
        # remove the seat number of other-existing passengers
        possibilities.discard(int(line, 2))
    for my_seat in possibilities:
        if(my_seat + 1 not in possibilities and my_seat - 1 not in possibilities):
            return my_seat
    raise("unable to find")


def main() -> int:
    parser = argparse.ArgumentParser(description="provide the input file")
    parser.add_argument('data_file', nargs='?', default=DEFAULT_INPUT)
    args = parser.parse_args()

    with open(args.data_file) as f, measure_time("day5:part2"):
        print(compute(f.read()))

    return 0


if __name__ == '__main__':
    exit(main())
