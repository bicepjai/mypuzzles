#!/bin/python

import sys
import random
from itertools import product
import time

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
    if n == 1 or n == 0:
        return False

    if n == 2 or n == 3 or n == 5 or n == 7:
        return True

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

def brute_force(first, last):
    count = 0
    primes = [2,3,5,7]
    for i in range(first, last):
        if miller_rabin(i):
            if all([long(d) in primes for d in str(i)]):
                # print(i)
                count += 1
    return count

def megaprimes(first, last):
    # print("-------------------megaprimes---------------")
    
    count = 0
    primes_c = ['2','3','5','7']
    primes = [2,3,5,7]

    first_digits = len(str(first))
    last_digits = len(str(last))
    
    # taking advantage of characters that match starting from first
    # saves time on large numbers in 10e9 range
    starting_digits = ""
    if first_digits == last_digits:
        for i,j in zip(str(first), str(last)):

            if i == j:
                starting_digits += i
                if i not in primes_c:
                    return 0
            else:
                break

    nof_digits = first_digits
    nof_starting_matching_digits = len(starting_digits)

    while nof_digits <= last_digits:

        if starting_digits:
            list_of_lists = [ primes_c for i in range(nof_digits-nof_starting_matching_digits)]
        else:
            list_of_lists = [ primes_c for i in range(nof_digits)]

        for n in list(product(*list_of_lists)):
            if starting_digits:
                n_str = starting_digits + "".join(n)
            else:
                n_str = "".join(n)

            mp = long(n_str)

            if mp >= first and mp <= last:
                if miller_rabin(mp):
                    count += 1
                    # print(mp)
        nof_digits += 1

    return count

def stress():
    max_range = 1000000000
    diff = 100000

    # max_range = 1000000000000000
    # diff = 1000000000    

    def get_first_last():
        fl = random.randint(1, max_range - diff - 2), random.randint(1, diff)
        # fl = random.randint(1, 10000), random.randint(1, 1000000000)
        return (fl[0], fl[0] + fl[1] )

    while True:
        print("------------------------------------")
        first, last = get_first_last()
        print("(first, last): ({}, {})".format(first, last))

        t1 = time.time()
        a_megaprime = megaprimes(first,last)
        t2 = time.time()
        print("a_megaprime: {} took {}".format(a_megaprime, t2-t1))

        # t3 = time.time()
        # b_megaprime = brute_force(first,last)
        # t4 = time.time()
        # print("b_megaprime: {} took {}".format(b_megaprime, t4-t3))

        # if b_megaprime != a_megaprime:
        #     print("NOT OK !!")
        #     break

# stress()
first,last = raw_input().strip().split(' ')
first,last = [long(first),long(last)]

# your code goes here
print(megaprimes(first,last))

