#! /usr/bin/python

import random, re, math
from collections import defaultdict
from itertools import *
from decimal import *

n = 5
l = n/2
sd = 1
nw = 1
i = 1
while l != 0:
		for j in range(1,5):
			nw = nw + 2*i
			sd = sd + nw
		i = i + 1
		l = l - 1
print sd
			
