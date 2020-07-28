# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1129
#!/usr/bin/env python2.7
# -*- coding : utf-8
while True:
	a = int(raw_input())
	if a == 0:
		break
	for i in xrange(a):
		entrada = [int(i)<=127 for i in raw_input().split()]
		if entrada.count(True)==1:
			print "ABCDE"[entrada.index(True)]
		else:
			print "*"
