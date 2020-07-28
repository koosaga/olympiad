# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1281
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
ordem = int(raw_input())
for i in xrange(ordem):
	dicio = {}
	quantidade1 = int(raw_input())
	for j in xrange(quantidade1):
		a,b = raw_input().split(" ")
		dicio[a] = float(b)
	quantidade2 = int(raw_input())
	soma = 0
	for j in xrange(quantidade2):
		c,d = raw_input().split(" ")
		soma += dicio[c] * int(d)
	print "R$ %.2f" % (soma)
