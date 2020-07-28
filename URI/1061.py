# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1061
# -*- coding: utf-8 -*-
d1 = int([k for k in raw_input().split(" ")][1])
h1,m1,s1 = [int(k) for k in raw_input().split(" ") if k != ":"]
d2 = int([k for k in raw_input().split(" ")][1])
h2,m2,s2 = [int(k) for k in raw_input().split(" ") if k != ":"]
total1 = (d1*24*3600) + (h1*3600) + (m1*60) + s1
total2 = (d2*24*3600) + (h2*3600) + (m2*60) + s2
diferenca = total2 - total1
for a,b in [("dia(s)",24*3600),("hora(s)",3600),("minuto(s)",60),("segundo(s)",1)]:
    exibir = int(diferenca/b)
    print "%d %s" % (exibir,a)
    diferenca %= b
