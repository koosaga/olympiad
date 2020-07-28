# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1546
# -*- coding: utf-8 -*-
ordem = int(raw_input())
casos = []
for i in xrange(ordem):
    subordem = int(raw_input())
    problemas = []
    for i in xrange(subordem):
        problemas.append(int(raw_input()))
    casos.append(problemas)
for teste in casos:
    for numero in teste:
        print {1:"Rolien",2:"Naej",3:"Elehcim",4:"Odranoel"}[numero]
