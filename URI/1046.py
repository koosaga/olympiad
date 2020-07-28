# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1046
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
a,b = [int(i) for i in raw_input().split(" ")]
if b <= a:
    b += 24
print "O JOGO DUROU %d HORA(S)" % (b-a)
