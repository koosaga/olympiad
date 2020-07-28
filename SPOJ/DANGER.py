# Ivan Carvalho
# Solution to https://www.spoj.com/problems/DANGER/
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
from math import log,floor
while True:
	entrada = raw_input()
	n = int(entrada[0] + entrada[1]) * 10 ** int(entrada[3])
	if n == 0:
		break
	expo = floor(log(n)/log(2))
	exibir = n - (2**expo)
	exibir *= 2
	exibir += 1
	print "%d" % (exibir)
