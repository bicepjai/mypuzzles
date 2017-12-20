#!/bin/python

import sys


n = int(raw_input().strip())
a_s = map(int, raw_input().strip().split(' '))
# your code goes here

def gcd (a,b):
    while b:
        a, b = b, a%b
    return a

gcds = set()
temp = 0

prefix_gcds = []
for a in a_s:
    prefix_gcds.append(gcd(temp,a))
    temp = a

suffix_gcds = []
for a in a_s[::-1]:
    suffix_gcds.append(gcd(temp,a))
    temp = a

print("prefix_gcds",prefix_gcds)
print("suffix_gcds",suffix_gcds)

debug=[]
for i,a in enumerate(a_s):
    if(i ==0):
        debug.append(suffix_gcds[1])
    elif(i == n-1):
        debug.append(prefix_gcds[n-2])
    else:
        debug.append(gcd(suffix_gcds[i+1],prefix_gcds[i-1]))
print(debug)

