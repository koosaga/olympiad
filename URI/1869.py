# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1869
#!/usr/bin/env python2.7
# -*- coding : utf -8 -*-
alfabeto = "0123456789ABCDEFGHIJKLMNOPQRSTUV"
dicio = {}
for i in xrange(len(alfabeto)):
	dicio[i] = alfabeto[i]
while True:
	n = int(raw_input())
	if n == 0:
		print "0"
		break
	invertido = []
	while n > 0:
		invertido.append(dicio[n%32])
		n /= 32
	print "".join(invertido)[::-1]
