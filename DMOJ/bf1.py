# Ivan Carvalho
# Solution to https://dmoj.ca/problem/bf1
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
a = int(raw_input())
v = []
for i in xrange(a):
	j = int(raw_input())
	v.append(j)
v.sort()
for i in v:
	print i