
from typing import Iterator
from Helper.helper import measure_time
import pytest
import argparse
import itertools


def compute(s: str) -> int:
    numbers = [int(number) for number in s.split()]

    for(a, b, c) in itertools.combinations(numbers, 3):
        if a + b + c == 2020:
            return a * b * c

    raise NotImplementedError


@pytest.mark.parametrize(
    ('input_s', 'expected'),
    (
        ('1721 979 366 299 675 1456', 514579),
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
