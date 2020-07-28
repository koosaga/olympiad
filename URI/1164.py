# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1164
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
ordem = int(raw_input())
def divisores(x):
    return [k for k in xrange(1,int(x/2)+1) if x%k==0]
for i in xrange(ordem):
    entrada = int(raw_input())
    if sum(divisores(entrada))==entrada:
        print "%d eh perfeito" % entrada
    else:
        print "%d nao eh perfeito" % entrada
