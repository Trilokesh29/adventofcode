
from Helper.helper import measure_time
import pytest
import argparse
from typing import List


def compute_move(lines: List[str], col: int, row: int):
    x, y = 0, 0
    count = 0
    x += col
    x %= len(lines[0])
    y += row
    while(y < len(lines)):
        if(lines[y][x] == '#'):
            count += 1
        x += col
        x %= len(lines[0])
        y += row

    return count


def compute(s: str) -> int:
    lines = s.splitlines()
    return(
        compute_move(lines, 1, 1) *
        compute_move(lines, 3, 1) *
        compute_move(lines, 5, 1) *
        compute_move(lines, 7, 1) *
        compute_move(lines, 1, 2))


INPUT = '''\
..##.......
#...#...#..
.#....#..#.
..#.#...#.#
.#...##..#.
..#.##.....
.#.#.#....#
.#........#
#.##...#...
#...##....#
.#..#...#.#
'''


@pytest.mark.parametrize(
    ('input_s', 'expected'),
    (
        (INPUT, 336),
    ),
)
def test(input_s: str, expected: int) -> None:
    assert compute(input_s) == expected


def main() -> int:
    parser = argparse.ArgumentParser(description="provide the input file")
    parser.add_argument('data_file')
    args = parser.parse_args()

    with open(args.data_file) as f, measure_time("day3:part2"):
        print(compute(f.read()))

    return 0


if __name__ == '__main__':
    exit(main())
