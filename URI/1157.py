# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1157
#!/usr/bin/env python2.7
# encoding : utf-8
x = int(raw_input())
for i in [k for k in xrange(1,int(x/2)+1) if x % k == 0]+[x]:
	print i
