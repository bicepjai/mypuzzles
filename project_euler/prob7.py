#! /usr/bin/python


def sieveE(n):
	sieve = [True] * (n+1)
	primes = []
	for i in xrange(2,n,2):
		sieve[i] = False
	sieve[1] = False
	sieve[2] = True
	primes.append(2)
	for i in xrange(1,n,2):
		if (sieve[i] == True):
			primes.append(i)
			for j in range(i,(n/i)+1):
				sieve[i*j] = False
	print len(primes)
	print primes[10000]

sieveE(1000000)