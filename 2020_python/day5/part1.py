
from Helper.helper import measure_time
import pytest
import argparse
import os

DEFAULT_INPUT = os.path.join(os.path.dirname(__file__), 'input.txt')


def compute(s: str) -> int:
    maximum = 0
    for line in s.splitlines():
        line = line.replace('F', '0').replace('B', '1')
        line = line.replace('R', '1').replace('L', '0')
        maximum = max(maximum, int(line, 2))

    return maximum


@ pytest.mark.parametrize(
    ('input_s', 'expected'),
    (
        ("BFFFBBFRRR", 567),
    ),
)
def test(input_s: str, expected: int) -> None:
    assert compute(input_s) == expected


def main() -> int:
    parser = argparse.ArgumentParser(description="provide the input file")
    parser.add_argument('data_file', nargs='?', default=DEFAULT_INPUT)
    args = parser.parse_args()

    with open(args.data_file) as f, measure_time("day5:part1"):
        print(compute(f.read()))

    return 0


if __name__ == '__main__':
    exit(main())
