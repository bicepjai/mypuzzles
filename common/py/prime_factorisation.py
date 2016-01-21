#! /usr/bin/python

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
	
def factor(n):
	if(miller_rabin(n)):
		print n
		return
	d=pollard(n)
	if(d!=n):
		factor(d)
		factor(n/d)
	else:
		factor(n)    
    
factor(8773536678)