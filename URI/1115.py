# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1115
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
while True:
    x,y = [int(k) for k in raw_input().split(" ")]
    if x == 0 or y == 0:
        break
    else:
        if x > 0 and y > 0:
            print "primeiro"
        elif x < 0 and y > 0:
            print "segundo"
        elif x < 0 and y < 0:
            print "terceiro"
        else:
            print "quarto"
