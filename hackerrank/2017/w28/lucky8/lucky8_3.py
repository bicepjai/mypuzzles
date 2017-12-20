from itertools import chain, combinations
from time import time
import collections
from random import randint


def powerset(iterable):
    "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(len(s) + 1))


def lucky_8_naive(n_str):
    power_set = (list(map(''.join, powerset(n_str))))
    div_l = []
    for s in power_set:
        if(s == ""):
            continue
        e = int(s)
        if(e % 8 == 0):
            div_l.append(s)
    return div_l, len(div_l)


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
    for units in div81d:
        print("[{}], {}".format(units, div81d[units]))


def print_div8_2d(div82d):
    for (tens,units) in div82d:
        if(div82d[(tens, units)]["units"] != 0 or div82d[(tens, units)]["tens"] != 0):
                print("[{},{}] => {}:{}, {}:{}"
                      .format(tens,units,
                      units, div82d[(tens,units)]["units"],
                      tens, div82d[(tens,units)]["tens"]))


def print_div8_3d(div83d):
    for ((hundreds, tens, units),d) in div83d:
            # if(d["units"] != 0 or d["tens"] != 0 or d["hundreds"] != 0):
            if (hundreds, tens, units) == ('2','8','8'):
                print("[{},{},{}] => {}:{}, {}:{}, {}:{:d}"
                      .format(hundreds, tens, units,
                      units, d["units"],
                      tens, d["tens"],
                      hundreds, d["hundreds"]))

mod_n = 1000000007


def get_div8_xds():
    #============ single digit nos divisible by 8
    # the dictionary is constructed after looking into 1 digit nos divisible
    # by 8
    div8_1d = {'0':0,'8':0}

    #============ double digit nos divisible by 8
    # the dictionary is constructed after looking into 2 digit nos divisible
    # by 8
    div8_2d = {}
    for i in range(10, 100):
        if i % 8 == 0:
            digits = tuple(str(i))
            div8_2d[digits] = {'units':0, 'tens':0}
    div8_2d[('0','0')] ={'units':0, 'tens':0}
    div8_2d[('0','8')] ={'units':0, 'tens':0}

    #============ triple digit nos divisible by 8
    # any number with last 3 digits divisible by 8 is divisible by 8
    # we are trying to track how many numbers are prefixed to a sequence of
    # 3 digit numbers divisible by 8
    # count is used to take into count the similar occurrence of hundreds digit in
    # nos divisible by 8, also used to see whether the digit is considered
    # the dictionary is constructed after looking into 3 digit nos divisible
    # by 8
    div8_3d = []
    for (tens, units) in div8_2d:
        div8_3d.append((('0',tens, units),{'units':0, 'tens':0, 'hundreds':0}))
    for i in range(100, 1000):
        if i % 8 == 0:
            digits = tuple(str(i))
            div8_3d.append((digits,{'units':0, 'tens':0, 'hundreds':0}))

    return div8_1d, div8_2d, div8_3d


def lucky_8_best(n_str):

    # single/double/triple on-line updates counter
    n = 0

    div8l = []
    dig1 = 0
    dig2 = 0
    dig3 = 0

    div8_1d, div8_2d, div8_3d = get_div8_xds()
    n_len = len(n_str)
    # process character by character from lsb
    for cur_pos, ch in enumerate(list(n_str[::-1])):
        # ci = int(ch)
        print("pos:",cur_pos,"=========================================", ch)

        #----------- update single digit dict
        if ch in div8_1d:
            print("single units update",ch)
            div8_1d[ch] += 1
            n += 1
            dig1 += 1

        #----------- update double digit dict
        for (tens,units) in div8_2d:
            # we have to process tens digit first
            # since we might process units for the first time and then end up updating tens
            # marking tens digit if units digit exists
            if div8_2d[(tens,units)]["units"] > 0 and ch == tens:
                print((tens,units),"double tens update")
                div8_2d[((tens,units))]["tens"] += 1
                n += div8_2d[((tens,units))]["units"]
                dig2 += div8_2d[((tens,units))]["units"]

        for (tens,units) in div8_2d:
            # marking units digit of double digit when found
            if ch == units and ((div8_2d[(tens,units)]["tens"] >= 0)):
                print((tens,units),"double units update")
                div8_2d[((tens,units))]["units"] += 1

        #----------- update triple digit dict

        # we have to process digits in order hundreds, tens
        # since we might process tens for the first time and then end up updating hundreds
        # marking hundreds digit if tens digit exists

        for i,((hundreds, tens, units),d) in enumerate(div8_3d):
            if (ch == hundreds) and (d["units"] > 0) and (d["tens"] > 0) :

                units_tens_count = (d["units"] * d["tens"]) % mod_n
                print("units_tens_count", units_tens_count,
                      "pow2", power(2, n_len - cur_pos - 1, mod_n))

                # reason we do 2 power is because, it covers all
                # possible prefixes
                count = (power(2, n_len - cur_pos - 1, mod_n)
                         * units_tens_count) % mod_n
                div8_3d[i][1]["hundreds"] += count
                n += count
                dig3 += count
                print((hundreds, tens, units), "triple hundreds update",count,"entries")

        for i,((hundreds, tens, units),d) in enumerate(div8_3d):
            # updating tens digit if units digit exists
            if (ch == tens) and (d["units"] > 0) and ((d["hundreds"] == 0) or (tens == hundreds and hundreds == units) ):
                print((hundreds, tens, units), "triple tens update")
                div8_3d[i][1]["tens"] += 1
            elif (ch == tens) and (d["units"] > 0) and ((d["hundreds"] > 0)):
                print("triple tens update new entry",(hundreds, tens, units),d)
                div8_3d.append(((hundreds, tens, units),{'units':0, 'tens':0, 'hundreds':0}))

        for i,((hundreds, tens, units),d) in enumerate(div8_3d):
            # updating units digit of double digit when found
            if (ch == units) and ((d["tens"] == 0) ):
                print((hundreds, tens, units), "triple units update")
                div8_3d[i][1]["units"] += 1
            elif (ch == units) and ((d["tens"] > 0) ):
                print("triple units update new entry",(hundreds, tens, units),d)
                div8_3d.append(((hundreds, tens, units),{'units':0, 'tens':0, 'hundreds':0}))

        # print("div8_1d------/n", div8_1d)
        # print("div8_2d------/n", div8_2d)
        # print("div8_3d------/n", div8_3d)
        print_div8_1d(div8_1d)
        print_div8_2d(div8_2d)
        print_div8_3d(div8_3d)
        print("dig1",dig1,"dig2",dig2,"dig3",dig3)

    return n


def random_with_N_digits(n):
    range_start = 10**(n - 1)
    range_end = (10**n) - 1
    return randint(range_start, range_end)


def stress_test():
    success = True
    test_i = 0
    size = 5
    while(success):
        n_str = str(random_with_N_digits(size))
        print(test_i,"====================================", n_str)
        best = lucky_8_best(n_str)
        print("lucky_8_best", best)
        div8_l, naive = lucky_8_naive(n_str)
        print("lucky_8_naive", naive)
        print(div8_l)
        if(best != naive):
            print(test_i,"failed_str", n_str)
            success = False
        test_i += 1
        if(test_i > 10**size):
            print("Ran", test_i, "tests")
            break

stress_test()
# n_str = '0123456789'
# n_str = '1234567890'
# n_str = '968'

# stress test fixes
# n_strs = ["7224", "6664", "3336","9868","2000"]
# n_strs = ["28888"]
# passed = []
# for n_str in n_strs:
#     print("====================================", n_str)
#     best = lucky_8_best(n_str)
#     print("lucky_8_best", best)
#     div8_l,naive = lucky_8_naive(n_str)
#     print("lucky_8_naive", naive)
#     if naive != best:
#         passed.append((n_str,False))
#     else:
#         passed.append((n_str,True))
#     print(div8_l)

# print("passed:",passed)

# main
# n = int(raw_input().strip())
# number = raw_input().strip()

# if(n <= 9):
#     print(lucky_8_naive(number))
# else:
#     print(lucky_8_best(number))
