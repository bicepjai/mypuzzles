#! /usr/bin/python

def collatz(a):
	if(a%2 == 0):
		return (a/2)
	else:
		return (3*a + 1)

limit = 1000000
collatzl = [0,1]
long_c = 0
no = 0
for i in xrange(2,limit):
		n = i
		c = 0
		while(n > 1):
			n = collatz(n)
			if(n < len(collatzl)):
				c = c + collatzl[n] + 1
				break
			c = c + 1
		collatzl.append(c)

print collatzl.index(max(collatzl))


 				
# took 44 sec
# limit = 1000000
# long_c = 0
# no = 0
# checked = [0]*limit
# for i in xrange(1,limit):
# 	if(checked[i] == 0):
# 		n = collatz(i)
# 		chain = 0
# 		while(n != 1):
# 			if(n<limit):
# 				checked[n]=1
# 			chain = chain + 1
# 			n = collatz(n)
# 		if (long_c < chain):
# 			long_c = chain
# 			no = i
# 
# print no,long_c
		
# took 1 min 55 sec
# limit = 1000000
# long_c = 0
# no = 0
# for i in xrange(1,limit):
# 		n = collatz(i)
# 		chain = 0
# 		while(n != 1):
# 			chain = chain + 1
# 			n = collatz(n)
# 		if (long_c < chain):
# 			long_c = chain
# 			no = i
# 
# print no,long_c