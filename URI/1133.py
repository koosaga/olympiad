# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1133
#!/usr/bin/env python2.7
# encoding : utf-8
a = int(raw_input())
b = int(raw_input())
x,y = sorted([a,b])
for i in [k for k in xrange(x+1,y) if k % 5 == 2 or k % 5 == 3]:
	print i
