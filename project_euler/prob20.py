#! /usr/bin/python

def factorial(a):
	if(a == 0):
		return 1
	else:
		return a * factorial(a-1)
		
s = 0
for c in str(factorial(100)):
	s = s + int(c)

print s