#! /usr/bin/python

import datetime
import time

sundays = 0
for year in range(1901, 2001):
    for month in range(1, 13):
        day = datetime.date(year, month, 1)
        if day.weekday() == 6:
            sundays += 1
 
print sundays