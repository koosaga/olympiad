# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1914
#!/usr/bin/env python2.7
# encoding : utf-8
ordem = int(raw_input())
for i in xrange(ordem):
	a,b,c,d = raw_input().split(" ")
	e,f = [int(k) for k in raw_input().split(" ")]
	if b == "PAR":
		if (e+f) % 2 == 0:
			print a
		else:
			print c
	else:
		if (e+f) % 2 == 0:
			print c
		else:
			print a
