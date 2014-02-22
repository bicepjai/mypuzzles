#!/usr/bin/python

import sys
import math

def check_order(l):
	return all(l[i] == l[i+1]-1 for i in xrange(len(l)-1))
	
def shuffle(l,N,K):
	k = 0
	p = N/K
	nl = [N+1]*N
	for i in range(p,0,-1):
		for j in range(K,0,-1):
			# print i,j,(p*j) - i
			nl[k] = l[(p*j) - i]
			k = k + 1
	return nl
	
def card_shuffle(N,K):
	l = range(0,N)
	# print l
	s = 1
	l = shuffle(l,N,K)
	# print l
	while (not check_order(l)):
		l = shuffle(l,N,K)
		# print l
		s = s + 1
	return s
	


T = int(raw_input())
for c in range(0,T):
	nk = [int(x) for x in (raw_input().split())]
	n = nk[0]
	k = nk[1]
	if c == T-1:
		print card_shuffle(n,k),
	else:
		print card_shuffle(n,k)
