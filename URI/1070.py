# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1070
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
entrada = int(raw_input())
if entrada % 2 == 0:
    entrada += 1
for i in xrange(6):
    print entrada + i*2
