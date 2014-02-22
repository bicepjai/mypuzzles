#!/usr/bin/python

# Import the system library. This allows us to access stdin later.
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

T = long(raw_input())
for t in range(1,T+1):
	N, pd, pg = [int(x) for x in raw_input().split()]
	D = 100/(__gcd(pd,100))
	if((D > N) or (pg == 100 and pd != 100) or (pg == 0 and pd != 0) ):
		print "Case #%d: Broken" % t
	else:
		print "Case #%d: Possible" % t