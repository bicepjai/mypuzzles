#! /usr/bin/python

import random, re, math
from collections import defaultdict
from itertools import *
from decimal import *

def pandigital(m1,m2,p):
	s = 0
	while(m1 != 0):
		s = s + m1%10
		m1 = m1/10
	while(m2 != 0):
		s = s + m2%10
		m2 = m2/10
	while(p != 0):
		s = s + p%10
		p = p/10
	if s == 45:
		return True
	else:
		return False

def formno(nos):
	noc = ''
	for c in nos:
		noc = noc + c
	return int(noc)
	
numlist = ['1','2','3','4','5','6','7','8','9']
sum = 0
sumlist = []

for digits in permutations(numlist):
	if formno(digits[:1]) * formno(digits[1:5]) == formno(digits[5:9]):
		print digits
		if not formno(digits[5:9]) in sumlist:
			sum = sum + formno(digits[5:9])
			sumlist.append(formno(digits[5:9]))
	if formno(digits[:2]) * formno(digits[2:5]) == formno(digits[5:9]):
		print digits
		if not formno(digits[5:9]) in sumlist:
			sum = sum + formno(digits[5:9])
			sumlist.append(formno(digits[5:9]))
	if formno(digits[:3]) * formno(digits[3:5]) == formno(digits[5:9]):
		print digits
		if not formno(digits[5:9]) in sumlist:
			sum = sum + formno(digits[5:9])
			sumlist.append(formno(digits[5:9]))
	if formno(digits[:4]) * formno(digits[4:5]) == formno(digits[5:9]):
		print digits
		if not formno(digits[5:9]) in sumlist:
			sum = sum + formno(digits[5:9])
			sumlist.append(formno(digits[5:9]))

			
print sumlist			
print sum					
					