# Enter your code here. Read input from STDIN. Print output to STDOUT
#! /usr/bin/python

__author__ = 'Jay <bicepjai@gmail.com>'
      
str1 = str(raw_input())
str2 = str(raw_input())
dicty1 = {}
dicty2 = {}
ans = 0
for c1 in str1:
    if c1 not in dicty1:
        dicty1[c1] = 1
    else:
        t = dicty1[c1]
        t = t + 1
        dicty1[c1] = t

for c2 in str2:
    if c2 not in dicty2:
        dicty2[c2] = 1
    else:
        t = dicty2[c2]
        t = t + 1
        dicty2[c2] = t       

for c1 in dicty1:
    if c1 not in dicty2:
        ans += dicty1[c1]
    else:
        if dicty1[c1] > dicty2[c1]:
            ans += dicty1[c1] - dicty2[c1]

for c2 in dicty2:
    if c2 not in dicty1:
        ans += dicty2[c2]
    else:
        if dicty2[c2] > dicty1[c2]:
            ans += dicty2[c2] - dicty1[c2]

print ans