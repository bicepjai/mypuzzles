#! /usr/bin/python

__author__ = 'Jay <bicepjai@gmail.com>'
      
line1 = str.split(str(raw_input()))
line2 = str.split(str(raw_input()))

N,K1,Q = map(int, line1)
K = K1 % N
X = map(int, line2)
# print X

for i in range(0,K):
    ele0 = X.pop()
    X.insert(0,ele0)
# print X
    
for i in range(0,Q):
    q = int(raw_input())
    print X[q]
