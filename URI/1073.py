# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1073
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
ordem = int(raw_input())
for i in xrange(2,ordem+1,2):
    print "%d^2 = %d" % (i,i**2)
