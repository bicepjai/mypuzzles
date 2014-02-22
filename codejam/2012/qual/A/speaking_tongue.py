#! /usr/bin/python

import sys,math
__author__ = 'Jay <bicepjai@gmail.com>'
str1 = 'ejp mysljylc kd kxveddknmc re jsicpdrysi rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd de kr kd eoya kw aej tysr re ujdr lkgc jv y e q z';
str2 = 'our language is impossible to understand there are twenty six factorial possibilities so it is okay if you want to just give up a o z q';
str_map = {}
for i in xrange(0,len(str1)):
	str_map[str1[i]] = str2[i];

T = int(raw_input())
for case in range(1,T+1):
	data= raw_input()
	result = ''.join([str_map[x] for x in data])
	print "Case #%(case)d: %(result)s" % {'case':case, 'result':result}
