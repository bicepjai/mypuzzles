#! /usr/bin/python


def sieveE_prime_addition(n):
	sieve = [True] * (n+1)
	for i in xrange(2,n,2):
		sieve[i] = False
	sieve[1] = False
	sieve[2] = True
	primes = 2
	for i in xrange(1,n,2):
		if (sieve[i] == True):
			primes = primes + i
			for j in range(i,(n/i)+1):
				sieve[i*j] = False
	print primes

sieveE_prime_addition(2000000)