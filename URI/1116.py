# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1116
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
ordem = int(raw_input())
for onomatopeia in xrange(ordem):
    a,b = [float(i) for i in raw_input().split(" ")]
    try:
        print "%.1f" % (a/b)
    except ZeroDivisionError:
        print "divisao impossivel"
