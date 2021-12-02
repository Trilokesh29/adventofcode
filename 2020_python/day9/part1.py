

from typing import List
from Helper.helper import measure_time
import pytest
import argparse
import os
import itertools


DEFAULT_INPUT = os.path.join(os.path.dirname(__file__), 'input.txt')


def compute(input: str, search: int = 25) -> int:

    visited: List[int] = []
    searchIndex = search - 1

    for index, line in enumerate(input.splitlines()):
        if index > searchIndex:
            lookUp = visited[-search:]
            for num1, num2 in itertools.combinations(lookUp, 2):
                if num1 + num2 == int(line):
                    break
            else:
                return int(line)
        visited.append(int(line))
    raise("result not found")


INPUT_S = '''\
35
20
15
25
47
40
62
55
65
95
102
117
150
182
127
219
299
277
309
576
'''


@ pytest.mark.parametrize(
    ('input_s', 'expected'),
    (
        (INPUT_S, 127),
    ),


)
def test(input_s: str, expected: int) -> None:
    assert compute(input_s, 5) == expected


def main() -> int:
    parser = argparse.ArgumentParser(description="provide the input file")
    parser.add_argument('data_file', nargs='?', default=DEFAULT_INPUT)
    args = parser.parse_args()

    with open(args.data_file) as f, measure_time("day9:part1"):
        print(compute(f.read()))

    return 0


if __name__ == '__main__':
    exit(main())
