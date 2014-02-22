#! /usr/bin/python

import sys, math, array

__author__ = 'Jay <bicepjai@gmail.com>'

names = [x.strip("\"") for x in raw_input().split(",")]
for i,name in enumerate(sorted(names)):
	for char in name:
		sum = sum + ((i+1) * (ord(char)-64))
print sum