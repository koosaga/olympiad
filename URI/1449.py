# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1449
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
ordem = int(raw_input())
exibir = False
for caso_da_vez in xrange(ordem):
	dicio = {}
	a,b = [int(i) for i in raw_input().split()]
	for i in xrange(a):
		entrada1 = raw_input()
		entrada2 = raw_input()
		dicio[entrada1] = entrada2
	for i in xrange(b):
		print " ".join([dicio.get(j,j) for j in raw_input().split()])
	print ""
