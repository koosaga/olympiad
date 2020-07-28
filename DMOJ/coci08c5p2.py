# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci08c5p2
from math import gcd

a,b = [int(i) for i in input().split()]

c = gcd(a,b)

i = 1
while i*i <= c:
	if c % i != 0:
		i += 1
		continue
	print("%d %d %d" % (i,a/i,b/i))
	if i*i != c:
		j = c/i
		print("%d %d %d" % (j,a/j,b/j))
	i += 1