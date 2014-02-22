#!/usr/bin/python

import sys
import math
	
def primeList(n):
	pp=2
	ep=[pp]
	pp+=1
	tp=[pp]
	ss=[2]
	lim = n
	while pp<int(lim):
		pp += ss[0]
		test = True
		sqrtpp = math.sqrt(pp)
		for a in tp:
		  if a > sqrtpp: break
		  if pp%a == 0:
		    test = False
		    break
		if test: tp.append(pp)
	ep.reverse()
	[tp.insert(0,a) for a in ep]
	return tp
	
def isPrime(num):
	if num <= 1:
		return 0
	if num == 2:
		return 1
	if num%2 == 0:
		return 0
	sRoot = int(math.sqrt(num));
	i = 3
	while i <= sRoot :
		if num%i == 0:
			return 0
		i += 2
	return 1

nofinp = int(raw_input())
# print nofinp
# print isPrime(nofinp)
# print primeList(nofinp)

if isPrime(nofinp):
	for i in range(0,nofinp-1):
		print "Hello world"
else:
	for i in range(0,nofinp-1):
		print "Hello codesprint"
		
if isPrime(nofinp):
		sys.stdout.write ("Hello world")
else:
		sys.stdout.write ("Hello codesprint")