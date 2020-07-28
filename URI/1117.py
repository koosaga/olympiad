# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1117
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
array = []
while True:
    entrada = float(raw_input())
    if entrada >= 0 and entrada <= 10:
        array.append(entrada)
    else:
        print "nota invalida"
    if len(array)==2:
        print "media = %.2f" % (sum(array)/2.0)
        break
