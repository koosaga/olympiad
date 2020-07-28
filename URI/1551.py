# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1551
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
ordem = int(raw_input())
frases = []
for i in xrange(ordem):
    frases.append(set([j for j in raw_input().replace(",","").replace(" ","")]))
for frase in frases:
    if len(frase) < 13:
        print "frase mal elaborada"
    elif len(frase) < 26:
        print "frase quase completa"
    else:
        print "frase completa"
