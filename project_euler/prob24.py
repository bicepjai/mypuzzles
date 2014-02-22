#! /usr/bin/python

import random
from collections import defaultdict
from itertools import *

permus = list(permutations(range(10)))
print ''.join(str(x) for x in list(permus[1000000-1]))