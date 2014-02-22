#! /usr/bin/python

import random, re, math
from collections import defaultdict
from itertools import *
from decimal import *

A = range(2,101)
B = range(2,101)

m=[]

for a in A:
	for b in B:
		e = a ** b
		if e not in m:
			m.append(e)

print len(m)