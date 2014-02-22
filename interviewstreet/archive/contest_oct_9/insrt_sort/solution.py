#!/usr/bin/python

import sys
import math

# print "Hello world"
# sys.stdout.write ("Hello world")

def insertion_sort_swaps(list2):
	swaps = 0
	for i in range(1, len(list2)):
		save = list2[i]
		j = i
		while j > 0 and list2[j - 1] > save:
			list2[j] = list2[j - 1]
			swaps = swaps + 1
			j -= 1
		list2[j] = save
	return swaps


T = int(raw_input())
for c in range(0,T):
	N = int(raw_input())
	list1 = [int(x) for x in (raw_input().split())]
	if c != T-1:
		print (insertion_sort_swaps(list1))
	else:
		sys.stdout.write (str(insertion_sort_swaps(list1)))	