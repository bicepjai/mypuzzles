#! /usr/bin/python

import sys,math
__author__ = 'Jay <bicepjai@gmail.com>'
comment = 1
T = int(raw_input())
for case in range(1,T+1):
	data= [int(x) for x in raw_input().split()]
	N=data[0];	S=data[1];
	p=data[2];	ti=data[3:]
	high_triplets = 0
	S1 = S
	for t in ti:
		scores = []
		remainder = t%3
		avg_score = t/3
		if(remainder == 2):
			if avg_score+1 >= p or avg_score >= p:
				high_triplets = high_triplets + 1
			elif S > 0 and avg_score+2 >= p:
				high_triplets = high_triplets + 1
				S = S-1
		elif (remainder == 1):
			if avg_score+1 >= p or avg_score >= p:
				high_triplets = high_triplets + 1
			elif S > 0 and avg_score+1 >= p:
				high_triplets = high_triplets + 1
				S = S-1
		elif (remainder == 0):
			if (avg_score >= p):
				high_triplets = high_triplets + 1
			elif S > 0 and avg_score > 0 and avg_score+1 >= p:
				high_triplets = high_triplets + 1
				S = S-1
	print "Case #%(case)d: %(result)d" % {'case':case, 'result':high_triplets}

