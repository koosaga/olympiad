# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1065
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
array = []
for i in xrange(5):
    array.append(int(raw_input())%2)
print "%d valores pares" % (5-sum(array))
