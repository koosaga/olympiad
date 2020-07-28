# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1170
# -*- coding: utf-8 -*-
from math import ceil as teto
from math import log10 as log
log2 = lambda x : log(x)/log(2)
ordem = int(raw_input())
for i in xrange(ordem):
    entradalinha = float(raw_input())
    print "%d dias" % int(teto(log2(entradalinha)))
