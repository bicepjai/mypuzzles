#! /usr/bin/python

def lcm (a,b):
	return (a*b)/gcd(b, a%b)
		
def gcd (a,b):
	if(a == 0 and b == 0):
		return 0
	elif(b == 0):
		return a
	elif(a == 0):
		return b
	else:
		return gcd(b, a%b)

ans = 1
for i in range(1,20):
	ans = lcm(ans,i)
print ans