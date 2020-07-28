# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1145
#!/usr/bin/env python2.7
a,b = [int(i) for i in raw_input().split(" ")]
for i in xrange(1,b+1,a):
	array = []
	for j in xrange(0,a):
		array.append(j+i)
	print " ".join([str(f) for f in array if f <= b])
