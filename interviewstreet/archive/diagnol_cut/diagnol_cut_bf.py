#!/usr/bin/python

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

def diagnol_cuts(M,N):
	print "lcm ",lcm([M,N])
	print "gcd ",gcd([M,N])
	
	m = float(M)
	n = float(N)
	# y = (n/m)*x
	intersections = []
	intersections_commons = []
	intersections_total = []
	for x in range(0,M):
		y = float(n/m)*x
		intersections.append((x,y))
		intersections_total.append((x,y))
	for y in range(0,N):
		x = float(m/n)*y
		intersections_total.append((x,y))
		if (x,y) not in intersections:
			intersections.append((x,y))
		else:
			intersections_commons.append((x,y))
	print "intersections_total"		
	print len(intersections_total)
	# print (intersections_total)
	print "intersections_commons"		
	print len(intersections_commons)
	print (intersections_commons)			
	print "intersections"
	print len(intersections)
	# print (intersections)
	
	

M = long(raw_input())
N = long(raw_input())
print (M,N)
diagnol_cuts(M,N)
# sys.stdout.write ("%d" % diagnol_cuts(M,N))

# print "Hello world"
# sys.stdout.write ("Hello world")