#!/usr/bin/python

# Import the system library. This allows us to access stdin later.
import sys
import math
import random
import itertools

#bruteforce

n, M = [int(x) for x in raw_input().split()]
conditions = []
count = 0
for m in xrange(1,M+1):
	conditions.append([int(x) for x in raw_input().split()])

i=0
for variablel in itertools.permutations(range(11),n):
	# print i,variablel
	i=i+1
	flag = 0
	
	for cond in conditions:
		x, y = cond[0],cond[1]
		# print x,y
		if (variablel[x] <= variablel[y]):
			flag =  flag + 1
			
	if flag == M:
		count = count + 1
		print i,variablel
		for cond in conditions:
			x, y = cond[0],cond[1]
			print "(",x,y,")",variablel[x],"<=",variablel[y]
			
print i,count,count%	1007
