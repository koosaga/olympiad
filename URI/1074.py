# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1074
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
ordem = int(raw_input())
for i in xrange(ordem):    
    entrada = int(raw_input())
    if entrada == 0:
        print "NULL"
    else:
        parouimpar = ["EVEN","ODD"][entrada%2]
        positivoounegativo = ["NEGATIVE","POSITIVE"][entrada>0]
        print "%s %s" % (parouimpar,positivoounegativo)
