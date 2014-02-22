#! /usr/bin/python


i = 1000
a = 1
while(i>0):
	a = a * 2
	i = i - 1
s = 0

while(a>0):
	s = s + a%10
	a = a/10
print s