#! /usr/bin/python

__author__ = 'Jay <bicepjai@gmail.com>'

# def prefix_table(p):
# 	m = len(p)
# 	pi = [0] * m
# 	k = 0
# 	for q in range(1, m):
# 		while k > 0 and p[k] != p[q]:
# 			k = pi[k - 1]
# 		if p[k] == p[q]:
# 			k = k + 1
# 		pi[q] = k
# 	# pi = [x+1 for x in pi]
# 	return pi
# 
# def kmp_matcher(t, p):
# 	n = len(t)
# 	m = len(p)
# 	pi = prefix_table(p)
# 	q = 0
# 	print pi
# 	for i in range(n):
# 		while q > 0 and p[q] != t[i]:
# 			q = pi[q - 1]
# 		if p[q] == t[i]:
# 			q = q + 1
# 		if q == m:
# 			return i - m + 1
# 	return -1
# 
# print kmp_matcher("banana","nan")


def savehumanity(t,p):
	n = len(t)
	m = len(p)
	q = 0
	f = 0
	for i in range(n-m):
		for j in range(m):
			if(t[i+j] == p[j]):
				q = q + 1
			else:
				f = f + 1
		
	return 0

T = int(raw_input())
for case in range(0,T):
	t = raw_input()
	p = raw_input()
	if case != T-1:
		empty = raw_input()
	savehumanity(t,p)
	
	
	
	