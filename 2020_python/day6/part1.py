
from Helper.helper import measure_time
import pytest
import argparse
from typing import List
import os

DEFAULT_INPUT = os.path.join(os.path.dirname(__file__), 'input.txt')


def compute(input: str) -> int:
    total_count = 0
    for answers in input.split('\n\n'):
        total_count += len(set(answers) - {' ', '\n'})

    return total_count


INPUT = '''\
abc

a
b
c

ab
ac

a
a
a
a

b
'''


@ pytest.mark.parametrize(
    ('input_s', 'expected'),
    (
        (INPUT, 11),
    ),
)
def test(input_s: str, expected: int) -> None:
    assert compute(input_s) == expected


def main() -> int:
    parser = argparse.ArgumentParser(description="provide the input file")
    parser.add_argument('data_file', nargs='?', default=DEFAULT_INPUT)
    args = parser.parse_args()

    with open(args.data_file) as f, measure_time("day6:part1"):
        print(compute(f.read()))

    return 0


if __name__ == '__main__':
    exit(main())
