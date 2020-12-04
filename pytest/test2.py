import subprocess
import random
import re
from time import time


def get_reference(s):
    match = re.match(r'^(1+)x(1+)=(1+)$', s)
    if not match:
        return False
    return len(match.group(1)) * len(match.group(2)) == len(match.group(3))


def gen_testcase(cnt=15, maxlen=15, fixlen=True):
    ret = []
    suc = cnt // 3
    for i in range(cnt - suc):
        length = random.randint(1, maxlen) if not fixlen else maxlen
        chars = [random.choice(['1', 'x', '=']) for j in range(length)]
        ret.append(''.join(chars))
    for i in range(suc):
        length = random.randint(1, maxlen) if not fixlen else maxlen
        maxm = round(length**0.5 - 1)
        m = random.randint(1, maxm)
        n = random.randint(1, maxm)
        m1 = '1'*m
        n1 = '1'*n
        mn = '1'*(m*n)
        ret.append(f'{m1}x{n1}={mn}')
    return ret


def make_test(cnt, l):
    tm_sum = 0
    for s in gen_testcase(cnt=cnt, maxlen=l):
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
    print(f'{cnt}*{l}: Total Time {round(tm_sum, 3)}s')


if __name__ == "__main__":
    tests = [(100, 100), (5000, 100), (100, 10000)]
    for i, tup in enumerate(tests):
        print(f'Test {i+1}')
        make_test(tup[0], tup[1])
