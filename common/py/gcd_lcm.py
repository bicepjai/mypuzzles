#! /usr/bin/python

def lcm (a,b):
	return (a*b)/gcd(b, a%b)

def gcd (a,b):
	while b:
		a, b = b, a%b
	return a
		
def gcd_understand (a,b):
	if(a == 0 and b == 0):
		return 0
	elif(b == 0):
		return a
	elif(a == 0):
		return b
	else:
		return gcd(b, a%b)

		
