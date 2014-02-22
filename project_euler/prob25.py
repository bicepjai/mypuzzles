#! /usr/bin/python

import random
from collections import defaultdict
from itertools import *

"""
def fibi(n,m):
	if n not in m:
		if n < 2:
			m[n] = n
		else:
			m[n] = fibi(n-1,m) + fibi(n-2,m)
	return m[n]		

print fibi(100, {})
"""

f0 = 0
f1 = 1
n = 100000
for i in range(2, n+1):
	f2 = f0 + f1
	f0 = f1
	f1 = f2
	if  len(str(f2)) == 1000:
		print i,f2,"\n"
		break;
