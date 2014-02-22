#! /usr/bin/python

def factorial(a):
	if(a == 0):
		return 1
	else:
		return a * factorial(a-1)
		
def combination(n,k):
	return factorial(n)/(factorial(k) * factorial(n-k))

# this problem taught pascals triangle and binomial theorem
print combination(40,20)