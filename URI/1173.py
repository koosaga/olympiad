# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1173
#!/usr/bin/env python2.7
# encoding : utf-8
entrada= int(raw_input())
array = [entrada*(2**i) for i in xrange(10)]
for a,b in enumerate(array):
	print "N[%d] = %d" % (a,b)
