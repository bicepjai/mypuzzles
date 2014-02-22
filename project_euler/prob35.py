#! /usr/bin/python

import random, re, math
from collections import defaultdict
from itertools import *
from decimal import *

def primes_sieve2(limit):
	a = [True] * limit
	a[0]=False
	a[1]=True
	primes = []
	for i in xrange(2,limit):
		if a[i]:
			primes.append(i)
			for j in xrange(i*i, limit, i):
				a[j] = False
	return primes
	
primes = primes_sieve2(1000000)

sum = 0
for n in primes:
	print n
	flag = True
	nos =[]
	while n != 0:
		nos.append(str(n%10))
		n = n/10
	nos.reverse()
	for i in range(1,len(nos)):
		cir_prime = (int(''.join((nos[i:]+nos[:i]))))
		if cir_prime not in primes:
			flag = False
	if flag:
		sum += 1
		
print sum
