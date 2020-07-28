# Ivan Carvalho
# Solution to https://dmoj.ca/problem/inaho4
n = int(raw_input())
a = [float(i) for i in raw_input().split()]
b = [float(i) for i in raw_input().split()]
total = 0
for i in xrange(len(a)):
	total += (b[i] - a[i])*(b[i] - a[i])
print "%.6f" % (total**0.5)