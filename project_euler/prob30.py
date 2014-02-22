#! /usr/bin/python

import random, re, math
from collections import defaultdict
from itertools import *
from decimal import *

po = 5
def powadd(n):
	s = 0
	while n > 0:
		r = n % 10
		s = s + (r ** po)
		n = n/ 10
	return s

A = range(2,powadd(999999))

s = 0
for a in A:
	if a == powadd(a):
		s = s + a
		print a
print s