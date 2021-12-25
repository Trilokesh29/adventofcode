
from Helper.helper import measure_time
import pytest
import argparse


def compute(s: str) -> int:
    numbers = list()
    for n_s in s.split():
        n = int(n_s)
        numbers.append(n)

    ref = list(numbers)[0]
    count = 0
    for num in numbers[1:]:
        if num > ref:
            count += 1
        ref = num
    return count


@pytest.mark.parametrize(
    ('input_s', 'expected'),
    (
        ('199 200 208 210 200 207 240 269 260 263', 7),
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
