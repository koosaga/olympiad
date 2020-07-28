# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1261
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
a,b = [int(i) for i in raw_input().split()]
dicio = {}
for caso_da_vez in xrange(a):
	c,d = raw_input().split()
	dicio[c] = int(d)
for caso_da_vez in xrange(b):
	resposta = 0
	vetor = []
	while True:
		texto = raw_input()
		if texto == ".":
			break
		else:
			for palavra in texto.split():
				resposta += dicio.get(palavra,0)
	print resposta
