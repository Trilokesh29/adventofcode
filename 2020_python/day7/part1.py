
from Helper.helper import measure_time
import pytest
import argparse
import os
import re
import collections

DEFAULT_INPUT = os.path.join(os.path.dirname(__file__), 'input.txt')
PATTERN = re.compile('^([^ ]+ [^ ]+) bags contain (.*)$')
BAG_RE = re.compile(r'(\d+) ([^ ]+ [^ ]+)')


def compute(s: str) -> int:
    parents = collections.defaultdict(list)
    for line in s.splitlines():
        match = PATTERN.match(line)
        assert match
        k = match[1]
        targets = [(int(n), tp) for n, tp in BAG_RE.findall(match[2])]

        for _, color in targets:
            parents[color].append(k)

    total_colors = set()
    todo = parents['shiny gold']

    while todo:
        color = todo.pop()
        if color not in total_colors:
            total_colors.add(color)
            todo.extend(parents[color])

    return len(total_colors)


INPUT_S = '''\
light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.
'''


@pytest.mark.parametrize(
    ('input_s', 'expected'),
    (
        (INPUT_S, 4),
    ),
)
def test(input_s: str, expected: int) -> None:
    assert compute(input_s) == expected


def main() -> int:
    parser = argparse.ArgumentParser(description="provide the input file")
    parser.add_argument('data_file', nargs='?', default=DEFAULT_INPUT)
    args = parser.parse_args()

    with open(args.data_file) as f, measure_time("day7:part1"):
        print(compute(f.read()))

    return 0


if __name__ == '__main__':
    exit(main())
