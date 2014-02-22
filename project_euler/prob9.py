#! /usr/bin/python

# using Euclid's formula http://en.wikipedia.org/wiki/Pythagorean_triple
for n in xrange (1,100):
	for m in xrange (n,100):
		a = m*m - n*n
		b = 2*m*n
		c = m*m + n*n
		if ((a + b + c) == 1000):
			print (a + b + c),a,b,c,a*b*c