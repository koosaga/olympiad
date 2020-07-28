# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1094
# -*- coding: utf-8 -*-

'''
Escreva a sua solução aqui
Code your solution here
Escriba su solución aquí
'''
ordem = int(raw_input())
dicio = {"C":0,"R":0,"S":0}
for i in xrange(ordem):
    a,b = raw_input().split()
    dicio[b] += int(a)
total = sum(dicio.values())
print "Total: %d cobaias" % total
print "Total de coelhos: %d" % dicio["C"]
print "Total de ratos: %d" % dicio["R"]
print "Total de sapos: %d" % dicio["S"]
print "Percentual de coelhos: %.2f %%" % (100.0*(dicio["C"]/float(total)))
print "Percentual de ratos: %.2f %%" % (100.0*(dicio["R"]/float(total)))
print "Percentual de sapos: %.2f %%" % (100.0*(dicio["S"]/float(total)))
