#! /usr/bin/python

target = 200
coins = [1,2,5,10,20,50,100,200]
ways = [1]+[0]*target
 
for coin in coins:
	for i in range(coin, target+1):
		print ways
		ways[i] += ways[i-coin]
		
print ways[i]
print "Answer to PE31 = ", ways[target]