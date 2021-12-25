
from Helper.helper import measure_time
import pytest
import argparse


def compute(s: str) -> int:

    hp = 0
    depth = 0

    for line in s.splitlines():
        command, count_s = line.split()
        count = int(count_s)
        if command == 'forward':
            hp += count
        elif command == 'down':
            depth += count
        else:
            depth -= count

    return hp * depth


INPUT_S = '''\
forward 5
down 5
forward 8
up 3
down 8
forward 2
'''


@pytest.mark.parametrize(
    ('input_s', 'expected'),
    (
        (INPUT_S, 150),
    ),
)
def test(input_s: str, expected: int) -> None:
    assert compute(input_s) == expected


def main() -> int:
    parser = argparse.ArgumentParser(description="provide the input file")
    parser.add_argument('data_file')
    args = parser.parse_args()

    with open(args.data_file) as f, measure_time("day1:part1"):
        print(compute(f.read()))

    return 0


if __name__ == '__main__':
    exit(main())
