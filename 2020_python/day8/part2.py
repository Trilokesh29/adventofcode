
from typing import List, Tuple
from Helper.helper import measure_time
import pytest
import argparse
import os

DEFAULT_INPUT = os.path.join(os.path.dirname(__file__), 'input.txt')


# The main purpose is to switch nop and jmp for a graceful exit


def trail_run(instruction: List[Tuple[str, int]], flip: int) -> int:
    acc_count = 0
    pc = 0
    Flip = {'jmp': 'nop', 'nop': 'jmp'}

    visited = set()
    while pc not in visited and pc < len(instruction):
        visited.add(pc)
        opc, value = instruction[pc]

        if pc == flip:
            opc = Flip[opc]

        if opc == 'acc':
            acc_count += value
            pc += 1
        elif opc == 'jmp':
            pc += value
        elif opc == 'nop':
            pc += 1
        else:
            raise("unknown instruction")

    if pc == len(instruction):
        return acc_count
    else:
        raise RuntimeError(visited)


def compute(s: str) -> int:
    instruction = []
    for line in s.splitlines():
        opc, opr_s = line.split()
        opr = int(opr_s)
        instruction.append((opc, opr))

    try:
        trail_run(instruction, -1)
    except RuntimeError as excp:
        visited, = excp.args
    else:
        raise AssertionError("impossible")

    for i in visited:
        print(instruction[i][0])
        if instruction[i][0] in {'nop', 'jmp'}:
            try:
                return trail_run(instruction, i)
            except RuntimeError:
                pass

    raise NotImplementedError('wat')


INPUT_S = '''\
nop +0
acc +1
jmp +4
acc +3
jmp -3
acc -99
acc +1
jmp -4
acc +6
'''


@ pytest.mark.parametrize(
    ('input_s', 'expected'),
    (
        (INPUT_S, 8),
    ),
)
def test(input_s: str, expected: int) -> None:
    assert compute(input_s) == expected


def main() -> int:
    parser = argparse.ArgumentParser(description="provide the input file")
    parser.add_argument('data_file', nargs='?', default=DEFAULT_INPUT)
    args = parser.parse_args()

    with open(args.data_file) as f, measure_time("day8:part2"):
        print(compute(f.read()))

    return 0


if __name__ == '__main__':
    exit(main())
