# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1018
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
entrada= int(raw_input())
print entrada
for i in [100,50,20,10,5,2,1]:
    total = int(entrada/i)
    print "%d nota(s) de R$ %d,00" % (total,i)
    entrada -= total*i
