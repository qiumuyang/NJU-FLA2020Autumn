import subprocess
import random
import re
from time import time


def get_reference(s):
    match = re.match(r'^(1+)x(1+)=(1+)$', s)
    if not match:
        return False
    return len(match.group(1)) * len(match.group(2)) == len(match.group(3))


def gen_full_testcase(length=10):
    total = []
    ret = ['1', 'x', '=']
    while len(ret[0]) < length:
        total += ret.copy()
        tmp = [s+c for s in ret for c in ['1', 'x', '=']]
        ret = tmp
    total += ret.copy()
    print(len(total))
    return total


def make_test(l):
    tm_sum = 0
    for s in gen_full_testcase(l):
        st = time()
        ret = subprocess.check_output("./turing tm/case2.tm " + s, shell=True)
        ed = time()
        tm_sum += ed - st
        ret = str(ret[:-1], encoding='utf8')
        refer = str(get_reference(s)).lower()
        if ret.lower() == refer.lower():
            pass
        else:
            print(f'{s:<30} should be {refer} output: {ret}')
    print(f'input from 1 to {l}: Total Time {round(tm_sum, 3)}s')


if __name__ == "__main__":
    make_test(6)
