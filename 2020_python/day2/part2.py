
from Helper.helper import measure_time
import pytest
import argparse
import collections


def compute(s: str) -> int:
    counter = 0
    for line in s.splitlines():
        r, c, p = line.split()
        r_min_s, r_max_s = r.split('-')
        r_min = int(r_min_s)
        r_max = int(r_max_s)
        c = c[0]
        counts_of_char = collections.Counter(p)[c]
        if (p[r_min - 1] == c) ^ (p[r_max - 1] == c):
            counter += 1

    return counter


INPUT_S = '''\
1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc
'''


@pytest.mark.parametrize(
    ('input_s', 'expected'),
    (
        (INPUT_S, 2),
    ),
)
def test(input_s: str, expected: int) -> None:
    assert compute(input_s) == expected


def main() -> int:
    parser = argparse.ArgumentParser(description="provide the input file")
    parser.add_argument('data_file')
    args = parser.parse_args()

    with open(args.data_file) as f, measure_time("day2:part2"):
        print(compute(f.read()))

    return 0


if __name__ == '__main__':
    exit(main())
