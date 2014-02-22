#! /usr/bin/python

n = 100

def sum_Nsquares(N):
	return N*(N+1)*(2*N+1)/6

def sum_N(N):
	return N*(N+1)/2

a = sum_Nsquares(n)
b = sum_N(n)
print (b*b - a)