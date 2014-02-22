#! /usr/bin/python

import random
from collections import defaultdict
from itertools import *
	
def gcd (a,b):
	while b:
		a, b = b, a%b
	return a
		
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

def pollard(n):
	if(n%2==0):
		return 2;
	x=random.randrange(2,n)
	c=random.randrange(2,n)
	y=x
	d=1
	while(d==1):
		x=(x*x+c)%n
		y=(y*y+c)%n
 		y=(y*y+c)%n
		d=gcd(x-y,n)
		if(d==n):
			break;
	return d;

global_factors = []
def factor(n):
	if(miller_rabin(n)):
		global_factors.append(n)
		return
	d=pollard(n)
	if(d!=n):
		factor(d)
		factor(n/d)
	else:
		factor(n)    

def getprimefactors(no):
	factor(no)
	global global_factors
	seq = global_factors
	global_factors = []
	seen = set()
	seen_add = seen.add
	return [ x for x in seq if x not in seen and not seen_add(x)]    

def sumofdivisors(no):
	if(no == 1):
		return 1
	else:
		s = 1
		primefactors = getprimefactors(no)
		divisor_list = []
		for prime in primefactors:
			i = 1
			p = i*prime
			while ( p < no):
				if( no % p == 0 and p not in divisor_list ):
					divisor_list.append(p)
					s = s + p
				i = i+1
				p = i*prime
		return s

abundant_nos = [12]

def isabundant(no):
	if no < sumofdivisors(no):
		return 1
	else:
		return 0
	
abundant = set(number for number in range(2, 30000) if isabundant(number) == 1)
sums = sorted(set(sum(c) for c in combinations_with_replacement(abundant, 2)))
print(sum(number for number in range(1,30000) if number not in sums))

