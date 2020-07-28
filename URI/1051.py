# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1051
# -*- coding: utf-8 -*-
e = float(raw_input())
if e <= 2000:
    print "Isento"
elif e <= 3000:
    print "R$ %.2f" % ((e-2000)*0.08)
elif e <= 4500:
    print "R$ %.2f" % ((e-3000)*0.18+80)
else:
    print "R$ %.2f" % ((e-4500)*0.28+80+1500*0.18)
