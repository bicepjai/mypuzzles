#! /usr/bin/python

import sys,math
__author__ = 'Jay <bicepjai@gmail.com>'

# T = int(raw_input())
# for case in range(1,T+1):
# 	A,B = [int(x) for x in raw_input().split()]
# 	# # A,B = [10,1000]
# 	result = 0
# 	for n in xrange(A,B+1):
# 		m=n; p=1
# 		while m != 0:
# 			p = p*10
# 			l = n%p
# 			m = n/p
# 			if n>p:
# 				other = int(str(l) + str(m))
# 				if n < other and other <= B:
# 					# print n,other
# 					result = result + 1
# 	print "Case #%(case)d: %(result)d" % {'case':case, 'result':result}

pre_2 = 36
pre_3 = 801
pre_4 = 12096
pre_5 = 161982
pre_6 = 2024451
pre_7 = 299997 # from 1000000 to 2000000

def getrecycle_nos(A,B):
	nofr = 0
	n = A
	while n <= B:
		n1=n; p=1
		while n1 != 0:
			p = p*10;	l = n%p; n1 = n/p
			if n>p:
				m = int(str(l) + str(n1))
				if n < m and m <= B and m >= A:
					nofr = nofr + 1
		n=n+1
	return nofr

T = int(raw_input())
for case in range(1,T+1):
	A,B = [int(x) for x in raw_input().split()]
	# result = 0
	# while A < B:
	# 	print "=>",A,B
	# 	no_of_digits = len(str(A))
	# 	start = A
	# 	end = int(math.pow(10,no_of_digits)) - 1
	# 	print " ",start,end
	result = getrecycle_nos(A,B)
	# 	A = A + (end - start)
	print "Case #%(case)d: %(result)d" % {'case':case, 'result':result}

