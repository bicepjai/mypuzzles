#!/usr/bin/python

# Import the system library. This allows us to access stdin later.
import sys
no_elements = 50
fib_series = [-1]*(no_elements+1)
fib_series[0] = 0
fib_series[1] = 1

def main():
	sum = 0
	fibi = 0
	i = 0
	while(fibi < 4000000):
		if (fibi%2 == 0):
			sum = sum + fibi
		fibi = fibonacci_n(i)
		i=i+1
	print sum

def fibonacci(n):
	if (fib_series[n] != -1):
		return fib_series[n]
	else:
		for i in range(2,n):
			fib_series[i] = fib_series[i-1] + fib_series[i-2]
		return fib_series[n]

def fibonacci_n(n):
	if (fib_series[n] != -1):
		return fib_series[n]
	else:
		fib_series[n] = fib_series[n-1] + fib_series[n-2]
		return fib_series[n]
				
main()