#! /usr/local/bin/python

def is_palindrome(n):
    s = str(n)
    return s == s[::-1]
 
ans = 0
for n1 in xrange(999, 100, -1):
    for n2 in xrange(n1, 100, -1):
        prod = n1 * n2
        if is_palindrome(prod) and (prod > ans):
            ans = prod
print ans