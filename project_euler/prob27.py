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

# def miller_rabin(n):
def is_prime(n):
	if n == 1:
		return False
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

A,B = 1000,1000
n1=0
for a in range(1,A):
	for b in range(1,B):
		n = 0
		p = (n * n) + (n * a) + b
		while is_prime(p):
			p = (n * n) + (n * a) + b
			n = n + 1
		if n > n1:
			print "+",a,"+",b,"(",abs(a*b),")","=> ",n
			n1 = n

n1=0
for a in range(1,A):
	for b in range(1,B):
		n = 0
		p = (n * n) - (n * a) + b
		while p != 0 and is_prime(abs(p)):
			p = (n * n) - (n * a) + b
			n = n + 1
		if n > n1:
			print "-",a,"+",b,"(",abs(a*b),")","=> ",n
			n1 = n
			
n1=0
for a in range(1,A):
	for b in range(1,B):
		n = 0
		p = (n * n) + (n * a) - b
		while p != 0 and is_prime(abs(p)):
			p = (n * n) + (n * a) - b
			n = n + 1
		if n > n1:
			print "+",a,"-",b,"(",abs(a*b),")","=> ",n
			n1 = n

n1=0
for a in range(1,A):
	for b in range(1,B):
		n = 0
		p = (n * n) - (n * a) - b
		while p != 0 and is_prime(abs(p)):
			p = (n * n) - (n * a) - b
			n = n + 1
		if n > n1:
			print "-",a,"-",b,"(",abs(a*b),")","=> ",n
			n1 = n			
			
			