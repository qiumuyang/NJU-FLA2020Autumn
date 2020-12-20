import subprocess
import random
import re
from time import time


def gen_bin(i):
    return bin(i)[2:]


def f(x):
    if x % 2 == 0:
        return x // 2
    return (x+1) // 2


def make_test(l):
    tm_sum = 0
    for i in range(l):
        s = gen_bin(i)
        st = time()
        ret = subprocess.check_output("./turing tm/hw3_2_1.tm " + s, shell=True)
        ed = time()
        tm_sum += ed - st
        ret = str(ret[:-1], encoding='utf8')
        refer = gen_bin(f(i))
        if ret == refer:
            pass
        else:
            print(f'{s:<15} should be {refer} output: {ret}')
    print(f'input from 0 to {l-1}: Total Time {round(tm_sum, 3)}s')


if __name__ == "__main__":
    make_test(1000)
