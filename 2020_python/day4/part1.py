
from Helper.helper import measure_time
import pytest
import argparse
from typing import List
import os

DEFAULT_INPUT = os.path.join(os.path.dirname(__file__), 'input.txt')

REQUIRED = frozenset(('byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid'))


def compute(input: str) -> int:
    count = 0
    for passport in input.split('\n\n'):
        fields_split = [inner_input.strip().split(':', 1)
                        for inner_input in passport.split()]
        fields = {k: v for k, v in fields_split}
        if fields.keys() >= REQUIRED:
            count += 1
    return count


INPUT = '''\
ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
byr:1937 iyr:2017 cid:147 hgt:183cm

iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884
hcl:#cfa07d byr:1929

hcl:#ae17e1 iyr:2013
eyr:2024
ecl:brn pid:760753108 byr:1931
hgt:179cm

hcl:#cfa07d eyr:2025 pid:166559648
iyr:2011 ecl:brn hgt:59in
'''


@ pytest.mark.parametrize(
    ('input_s', 'expected'),
    (
        (INPUT, 2),
    ),
)
def test(input_s: str, expected: int) -> None:
    assert compute(input_s) == expected


def main() -> int:
    parser = argparse.ArgumentParser(description="provide the input file")
    parser.add_argument('data_file', nargs='?', default=DEFAULT_INPUT)
    args = parser.parse_args()

    with open(args.data_file) as f, measure_time("day4:part1"):
        print(compute(f.read()))

    return 0


if __name__ == '__main__':
    exit(main())
