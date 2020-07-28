# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1020
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
entrada = int(raw_input())
for a,b in [(365,"ano(s)"),(30,"mes(es)"),(1,"dia(s)")]:
    total = int(entrada/a)
    print "%d %s" % (total,b)
    entrada -= total*a
