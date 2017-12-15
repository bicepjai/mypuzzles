
from itertools import chain, combinations
from time import time
import collections
from random import randint


def powerset(iterable):
    "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(len(s) + 1))


def lucky_8_naive(n_str):
    n = 0
    power_set = (list(map(''.join, powerset(n_str))))
    div_l = []
    for s in power_set:
        if(s == ""):
            continue
        e = int(s)
        if(e % 8 == 0):
            n += 1
            div_l.append(e)
    print(div_l)
    return n


def power(g_base, a, p_mod):
    x = 1
    bits = "{0:b}".format(a)
    for i, bit in enumerate(bits):
        if bit == '1':
            x = (((x**2) * g_base) % p_mod)
        elif bit == '0':
            x = ((x**2) % p_mod)
    return x % p_mod


def print_div8_1d(div81d):
    for units in collections.OrderedDict(sorted(div81d.items())):
        print("[{:d}], {:d}".format(units, div81d[units]["count"]))


def print_div8_2d(div82d):
    for units in collections.OrderedDict(sorted(div82d.items())):
        for tens in collections.OrderedDict(sorted(div82d[units].items())):
            if tens == "count": continue
            print("[{:d}][{:d}]".format(units, tens), div82d[units][tens]["count"])


def print_div8_3d(div83d):
    for units in collections.OrderedDict(sorted(div83d.items())):
        for tens in collections.OrderedDict(sorted(div83d[units].items())):
            if tens == "count": continue
            l = []
            for hundreds in collections.OrderedDict(sorted(div83d[units][tens].items())):
                if hundreds == "count": continue
                temp = "-"
                if div83d[units][tens][hundreds]["count"] > 0:
                    temp = div83d[units][tens][hundreds]["count"]
                l.append((hundreds, temp))
            print("[{:d}][{:d}]".format(units, tens), l)

mod_n = 1000000007


def get_div8_xds():
    #============ single digit nos divisible by 8
    # the dictionary is constructed after looking into 1 digit nos divisible by 8
    div8_1d = {
        0: {"count": 0}, 8: {"count": 0}
    }

    #============ double digit nos divisible by 8
    # the dictionary is constructed after looking into 2 digit nos divisible by 8
    div8_2d = {
        0: {"count": 0, 0: {"count": 0}, 4: {"count": 0}, 8: {"count": 0}},
        2: {"count": 0, 3: {"count": 0}, 7: {"count": 0}},
        4: {"count": 0, 2: {"count": 0}, 6: {"count": 0}},
        6: {"count": 0, 1: {"count": 0}, 5: {"count": 0}, 9: {"count": 0}},
        8: {"count": 0, 4: {"count": 0}, 8: {"count": 0}, 0: {"count": 0}}
    }

    #============ triple digit nos divisible by 8

    # any number with last 3 digits divisible by 8 is divisible by 8
    # we are trying to track how many numbers are prefixed to a sequence of
    # 3 digit numbers divisible by 8
    # count is used to take into count the similar occurrence of hundreds digit in
    # nos divisible by 8, also used to see whether the digit is considered

    # the dictionary is constructed after looking into 3 digit nos divisible by 8
    div8_3d = {}
    units = 0
    div8_3d[units] = {"count": 0}
    for tens in [0, 4, 8]:
        div8_3d[units][tens] = {hundreds: {"count": 0} for hundreds in [0, 2, 4, 6, 8]}
        div8_3d[units][tens]["count"] = 0
    for tens in [2, 6]:
        div8_3d[units][tens] = {hundreds: {"count": 0} for hundreds in [1, 3, 5, 7, 9]}
        div8_3d[units][tens]["count"] = 0

    units = 2
    div8_3d[units] = {"count": 0}
    for tens in [3, 7]:
        div8_3d[units][tens] = {hundreds: {"count": 0} for hundreds in [0, 2, 4, 6, 8]}
        div8_3d[units][tens]["count"] = 0
    for tens in [1, 5, 9]:
        div8_3d[units][tens] = {hundreds: {"count": 0} for hundreds in [1, 3, 5, 7, 9]}
        div8_3d[units][tens]["count"] = 0

    units = 4
    div8_3d[units] = {"count": 0}
    for tens in [2, 6]:
        div8_3d[units][tens] = {hundreds: {"count": 0} for hundreds in [0, 2, 4, 6, 8]}
        div8_3d[units][tens]["count"] = 0
    for tens in [0, 4, 8]:
        div8_3d[units][tens] = {hundreds: {"count": 0} for hundreds in [1, 3, 5, 7, 9]}
        div8_3d[units][tens]["count"] = 0

    units = 6
    div8_3d[units] = {"count": 0}
    for tens in [1, 5, 9]:
        div8_3d[units][tens] = {hundreds: {"count": 0} for hundreds in [0, 2, 4, 6, 8]}
        div8_3d[units][tens]["count"] = 0
    for tens in [3, 7]:
        div8_3d[units][tens] = {hundreds: {"count": 0} for hundreds in [1, 3, 5, 7, 9]}
        div8_3d[units][tens]["count"] = 0

    units = 8
    div8_3d[units] = {"count": 0}
    for tens in [0, 4, 8]:
        div8_3d[units][tens] = {hundreds: {"count": 0} for hundreds in [0, 2, 4, 6, 8]}
        div8_3d[units][tens]["count"] = 0
    for tens in [2, 6]:
        div8_3d[units][tens] = {hundreds: {"count": 0} for hundreds in [1, 3, 5, 7, 9]}
        div8_3d[units][tens]["count"] = 0

    return div8_1d, div8_2d, div8_3d


def lucky_8_best(n_str):

    # double digit and triple digit needs on-line updates
    # since before/after units/tens/hundreds needs to be considered
    n = 0

    div8_1d, div8_2d, div8_3d = get_div8_xds()
    n_len = len(n_str)
    # process character by character from lsb
    for cur_pos, ch in enumerate(list(n_str[::-1])):
        ci = int(ch)
        print("=========================================", ci)

        #----------- update single digit dict
        if ci in div8_1d.keys():
            div8_1d[ci]["count"] += 1

        #----------- update double digit dict
        for units in div8_2d.keys():
            # we have to process tens digit first
            # since we might process units for the first time and then end up updating tens
            # marking tens digit if units digit exists
            for tens in div8_2d[units]:
                if tens == "count":
                    continue

                if div8_2d[units]["count"] > 0 and ci == tens:
                    # print("double digit update",units,tens)
                    div8_2d[units][ci]["count"] += 1
                    n += div8_2d[units]["count"]
                    break

            # marking units digit of double digit when found
            if ci == units:
                # print("double digit exists update",ci)
                div8_2d[ci]["count"] += 1

        #----------- update triple digit dict

        # we have to process digits in order hundreds, tens
        # since we might process tens for the first time and then end up updating hundreds
        # marking hundreds digit if tens digit exists

        for units in div8_3d.keys():
            if units == "count": continue
            for tens in div8_3d[units].keys():
                if tens == "count": continue
                for hundreds in div8_3d[units][tens].keys():
                    if div8_3d[units][tens]["count"] > 0 and div8_3d[units]["count"] > 0 and ci == hundreds:
                        print("units", units, "tens", tens, "triple digit update", ci)
                        print("div8_3d[units][tens]",div8_3d[units][tens]["count"],"div8_3d[units]",div8_3d[units]["count"])
                        units_tens_count = (div8_3d[units]["count"] * div8_3d[units][tens]["count"]) % mod_n
                        print("units_tens_count",units_tens_count,"pow2",power(2, n_len - cur_pos - 1, mod_n))

                        # reason we do 2 power is because, it covers all possible prefixes
                        count = (power(2, n_len - cur_pos - 1, mod_n) * units_tens_count) % mod_n
                        div8_3d[units][tens][ci]["count"] += count
                        n += count

                # updating tens digit if units digit exists
                if ci == tens and div8_3d[units]["count"] > 0:
                    print("units", units, "tens", tens, "triple first tens update")
                    div8_3d[units][tens]["count"] += 1

            # updating units digit of double digit when found
            if ci == units and div8_3d[ci]["count"] == 0:
                print("units", units, "triple first units update")
                div8_3d[ci]["count"] += 1

        # print("div8_1d------/n", div8_1d)
        # print("div8_2d------/n", div8_2d)
        # print("div8_3d------/n", div8_3d)
        print_div8_1d(div8_1d)
        print_div8_2d(div8_2d)
        print_div8_3d(div8_3d)

    #---------- collect the counts off-line mode
    # single digit updates
    n += (div8_1d[0]["count"] + div8_1d[8]["count"])

    # triple digit updates
    # for units in div8_3d.keys():
    #     if units == "exist":
    #         continue
    #     for tens in div8_3d[units]:
    #         if tens == "exist":
    #             continue
    #         for hundreds in div8_3d[units][tens]:
    #             if hundreds == "exist":
    #                 continue
    #             n += div8_3d[units][tens][hundreds]["count"]

    return n


def random_with_N_digits(n):
    range_start = 10**(n - 1)
    range_end = (10**n) - 1
    return randint(range_start, range_end)


def stress_test():
    success = True
    while(success):
        n_str = str(random_with_N_digits(4))
        print("====================================", n_str)
        best = lucky_8_best(n_str)
        print("lucky_8_best", best)
        naive = lucky_8_naive(n_str)
        print("lucky_8_naive", naive)

        if(best != naive):
            print("failed_str", n_str)
            success = False

# stress_test()
# n_str = '0123456789'
# n_str = '1234567890'
# n_str = '968'

# stress test fixes
# n_str = "3696"
# n_str = "7224"
n_str = "8722"
# n_str = "2326"
# n_str = "9868"
print("====================================",n_str)
best = lucky_8_best(n_str)
print("lucky_8_best",best)
naive = lucky_8_naive(n_str)
print("lucky_8_naive",naive)

# main
# n = int(raw_input().strip())
# number = raw_input().strip()

# if(n <= 9):
#     print(lucky_8_naive(number))
# else:
#     print(lucky_8_best(number))
