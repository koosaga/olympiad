# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1165
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
ordem = int(raw_input())
array = []
for i in xrange(ordem):
    array.append(int(raw_input()))
def primo(x):
    return x == 2 or x > 1 and x%2==1 and all([x%i for i in xrange(3,int(x**0.5)+1,2)])
for k in array:
    if primo(k):
        print "%d eh primo" % (k)
    else:
        print "%d nao eh primo" % (k)
