# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1865
#!/usr/bin/env python2.7
# encoding : utf-8
ordem = int(raw_input())
for i in xrange(ordem):
	a,b = raw_input().split(" ")
	if a == "Thor":
		print "Y"
	else:
		print "N"
