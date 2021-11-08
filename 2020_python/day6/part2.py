
from Helper.helper import measure_time
import pytest
import argparse
from typing import List
import os

DEFAULT_INPUT = os.path.join(os.path.dirname(__file__), 'input.txt')


def compute(s: str) -> int:
    counts = 0
    for group in s.split('\n\n'):
        lines = group.splitlines()
        all_counted = set(lines[0])
        for other in lines[1:]:
            all_counted &= set(other)
        counts += len(all_counted)
    return counts


INPUT_S = '''\
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


@pytest.mark.parametrize(
    ('input_s', 'expected'),
    (
        (INPUT_S, 6),
    ),
)
def test(input_s: str, expected: int) -> None:
    assert compute(input_s) == expected


def main() -> int:
    parser = argparse.ArgumentParser(description="provide the input file")
    parser.add_argument('data_file', nargs='?', default=DEFAULT_INPUT)
    args = parser.parse_args()

    with open(args.data_file) as f, measure_time("day6:part2"):
        print(compute(f.read()))

    return 0


if __name__ == '__main__':
    exit(main())
