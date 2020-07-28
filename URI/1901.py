# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1901
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
ordem = int(raw_input())
array = []
for i in xrange(ordem):
    array.append([int(k) for k in raw_input().split(" ")])
pares = []
for j in xrange(ordem*2):
    pares.append([int(l)-1 for l in raw_input().split(" ") ])
encontrados = []
for c,d in pares:
    encontrados.append(array[c][d])
print len(set(encontrados))
