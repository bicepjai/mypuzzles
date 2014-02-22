#!/usr/bin/python

import sys, re, math
from itertools import permutations

mswaps = 0
def merge(left, right):
	global mswaps
	result = []
	i ,j = 0, 0
	while i < len(left) and j < len(right):
		if left[i] <= right[j]:
 			result.append(left[i])
			i += 1
			mswaps += 1
		else:
			result.append(right[j])
			j += 1
	result += left[i:]
	result += right[j:]
	return result
	
def merge_sort(list):
	if len(list) < 2:
		return list
	middle = len(list) / 2
	left = merge_sort(list[:middle])
	right = merge_sort(list[middle:])
	return merge(left, right)

def mnofswaos(A):
			global mswaps
			mswaps = 0
			merge_sort(A)
			return mswaps
			
def insert_sort(N,Ai):
	swaps = 0
	for i in range(1,N):
		j=i
		while j>0 and Ai[j] < Ai[j-1]:
			a = Ai[j]
			Ai[j] = Ai[j-1]
			Ai[j-1] = a 
			j = j-1
			swaps = swaps + 1
	return swaps
	
T = int(raw_input())
for t in range(0,T):
	solutions = 0
	N= int(raw_input())
	B = [int(x) for x in raw_input().split()]
	if t == T-1:
		print mnofswaos(B),
	else:
		print mnofswaos(B)
