import subprocess
import random
import re
from time import time


def get_reference(str):
    return not not re.match(r'^(a+b+)\1$', str)


def gen_testcase(cnt=15, maxlen=15, fixlen=True):
    ret = []
    suc = cnt // 3
    for i in range(cnt - suc):
        length = random.randint(1, maxlen) if not fixlen else maxlen
        chars = [random.choice(['a', 'b']) for j in range(length)]
        ret.append(''.join(chars))
    for i in range(suc):
        length = random.randint(2, maxlen//2) if not fixlen else maxlen
        alen = random.randint(1, length - 1)
        blen = length - alen
        ab = 'a'*alen + 'b'*blen
        ret.append(ab*2)
    return ret


tm_sum = 0
cnt = 100
l = 20
for s in gen_testcase(cnt=cnt, maxlen=l):
    st = time()
    ret = subprocess.check_output("./turing tm/case1.tm " + s, shell=True)
    ed = time()
    tm_sum += ed - st
    ret = str(ret[:-1], encoding='utf8')
    refer = str(get_reference(s)).lower()
    if ret.lower() == refer.lower():
        pass
    else:
        print(f'{s:<30} should be {refer} output: {ret}')
print(f'{cnt}*{l}: Total Time {round(tm_sum, 3)}s')