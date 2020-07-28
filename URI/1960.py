# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1960
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
entrada = int(raw_input())
array = []
for a,b in [("M",1000),("CM",900),("D",500),("CD",400),("C",100),("XC",90),("L",50),("XL",40),("X",10),("IX",9),("V",5),("IV",4),("I",1)]:
    total = int(entrada/b)
    for k in xrange(total):
        array.append(a)
    entrada %= b
print "".join(array)
