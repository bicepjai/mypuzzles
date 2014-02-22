#!/usr/bin/python

import sys
import math

def lcm(numbers):
    return reduce(__lcm, numbers)

def gcd(numbers):
    return reduce(__gcd, numbers)

def __lcm(a, b):
    return ( a * b ) / __gcd(a, b)

def __gcd(a, b):
    a = int(a)
    b = int(b)
    while b:
        a,b = b,a%b
    return a

def diagnol_cuts(m,n):
	return m+n-gcd([m,n])
	


M = long(raw_input())
N = long(raw_input())
sys.stdout.write ("%d" % diagnol_cuts(M,N))

# print "Hello world"
# sys.stdout.write ("Hello world")