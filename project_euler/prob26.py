#! /usr/bin/python

import random, re, math
from collections import defaultdict
from itertools import *
from decimal import *

def miller_rabin_pass(a, s, d, n):
    a_to_power = pow(a, d, n)
    if a_to_power == 1:
        return True
    for i in xrange(s-1):
        if a_to_power == n - 1:
            return True
        a_to_power = (a_to_power * a_to_power) % n
    return a_to_power == n - 1

def miller_rabin(n):
    d = n - 1
    s = 0
    while d % 2 == 0:
        d >>= 1
        s += 1
    for repeat in xrange(20):
        a = 0
        while a == 0:
            a = random.randrange(n)
        if not miller_rabin_pass(a, s, d, n):
            return False
    return True

n = 997
for p in range(n, 1 ,-2):
    if not miller_rabin(p): continue
    c = 1
    while (pow(10, c) % p) -1 != 0:
        c += 1
    if (p-c) == 1: break
 
print "Answer to PE26 = ",p

