#! /usr/bin/python

import sys
numl = []
mem_sum = []

def memoize_sum(i,j):
	a = i+1
	br = j
	bl = j+1
	# print "=>","[",i,j,"]","comparing","[",a,bl,"]","[",a,br,"]",
	if(i != 0 and a > len(numl)-1):
		# print "..returning","[",i,j,"]",numl[i][j]
		mem_sum[i][j] = numl[i][j]
		return numl[i][j]
	else:
		if(numl[a][br] > numl[a][bl]):
			# print "=r[",a,br,"]"
			if(mem_sum[a][br] != -1):
				mem_sum[i][j] = numl[i][j] + mem_sum[a][br]
				# print i,j,mem_sum[i][j]
				return mem_sum[i][j]
			else:
				mem_sum[i][j] = numl[i][j] + memoize_sum(a,br)
				# print i,j,mem_sum[i][j]
				return mem_sum[i][j]
		else:
			# print "=l[",a,bl,"]"
			if(mem_sum[a][bl] != -1):
				mem_sum[i][j] = numl[i][j] + mem_sum[a][bl]
				# print i,j,mem_sum[i][j]
				return mem_sum[i][j]
			else:
				mem_sum[i][j] = numl[i][j] + memoize_sum(a,bl)
				# print i,j,mem_sum[i][j]
				return mem_sum[i][j]
	

for line in sys.stdin:
    numl.append([int(i) for i in line.split()])

for i in xrange(0,len(numl)):
	mem_sum.append([int(-1)]*(i+1))

g = 0
for i in xrange(0,len(numl)):
	for j in xrange(0,i+1):
		sum = memoize_sum(i,j)
		if(g < sum):
			g = sum

# print mem_sum
print g

table = numl
 
for row in range(len(table)-1, 0, -1):
  for col in range(0, row):
    table[row-1][col] += max(table[row][col], table[row][col+1])
 
print "Answer to PE18 = ", table[0][0]
	
