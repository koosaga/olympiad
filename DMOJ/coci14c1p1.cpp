// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c1p1
n = int(raw_input())
b = [int(i) for i in raw_input().split()]
total = b[0]
a = [b[0]]
for i in xrange(1,n):
	davez = b[i]*(i+1) - total
	a.append(davez)
	total += davez
for i in a:
	print i,