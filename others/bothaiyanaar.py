#! /usr/bin/python

import math

def pytha(a,b):
	return math.sqrt(pow(a,2) + pow(b,2))
	
def botha(a,b):
	return (float(a) - float(a/8) + float(b/2))

ranges = 101

for i in xrange(1,ranges):
	for j in xrange(1,ranges):
		if (pytha(i,j) == botha(i,j)):
			print "[",i,j,"]",
