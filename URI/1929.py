# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1929
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
def istriangle(x,y,z):
    return x+y > z and x+z > y and z+y>x
a,b,c,d = sorted([int(i) for i in raw_input().split(" ")])
if istriangle(a,b,c) or istriangle(a,b,d) or istriangle(a,c,d) or istriangle(b,c,d):
    print "S"
else:
    print "N"
