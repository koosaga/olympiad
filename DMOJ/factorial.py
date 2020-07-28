# Ivan Carvalho
# Solution to https://dmoj.ca/problem/factorial
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
mod = 2**32
testes = int(raw_input())
for vez in xrange(testes):
	fat = 1
	n = int(raw_input())
	if n >= 50:
		print 0
		continue
	for i in xrange(2,n+1):
		fat *= i
		fat %= mod
	print fat