# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1174
#!/usr/bin/env python2.7
# encoding : utf-8
array = []
for i in xrange(100):
	array.append(float(raw_input()))
for a,b in enumerate(array):
	if b <= 10:
		print "A[%d] = %.1f" % (a,b)
