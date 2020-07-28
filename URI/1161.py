# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1161
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
def fatorial(x):
    if x == 0:
        return 1
    else :
        return x * fatorial(x-1)
while True:
    try:
        a,b = [int(k) for k in raw_input().split(" ")]
        print fatorial(a) + fatorial(b)
    except EOFError:
        break
