# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1144
#!/usr/bin/env python2.7
# encoding : utf-8
ordem = int(raw_input())
for i in xrange(1,ordem+1):
	print "%d %d %d" % (i,i**2,i**3)
	print "%d %d %d" % (i,i**2+1,i**3+1)
