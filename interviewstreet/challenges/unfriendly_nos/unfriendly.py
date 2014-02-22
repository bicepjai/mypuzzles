#!/usr/bin/python

# Import the system library. This allows us to access stdin later.
import sys
import math
import random
	
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

primes_clear_this = []	
def factor(n):
	if(miller_rabin(n)):
		if n not in primes_clear_this:
			primes_clear_this.append(n)
		return
	d=pollard(n)
	if(d!=n):
		factor(d)
		factor(n/d)
	else:
		factor(n)
		   
def get_prime_factors(n):
		global primes_clear_this
		primes_clear_this = []
		factor(n)
		return primes_clear_this

N, K = [int(x) for x in raw_input().split()]
unfriendly_nos = [int(x) for x in raw_input().split()]
friendliness = 0
for factor in get_prime_factors(K):
	k = K
	while (k):
		hurthim = 1
		for enemy in unfriendly_nos:
			if(enemy % (k) == 0):
				hurthim = 0
				break
		if hurthim == 1:
			friendliness = friendliness + 1
		k = k/factor
print friendliness
		
