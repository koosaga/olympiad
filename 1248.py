# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1248
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
ordem = int(raw_input())
for i in xrange(ordem):
	entrada1 = [k for k in raw_input()]
	entrada2 = [l for l in raw_input()]
	entrada3 = [q for q in raw_input()]
	try:
		for j in entrada2:
			entrada1.remove(j)
		for j in entrada3:
			entrada1.remove(j)
		print "".join(sorted(entrada1))
	except ValueError:
		print "CHEATER"
