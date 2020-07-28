# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1171
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
from collections import Counter
total = int(raw_input())
contador = Counter()
for i in xrange(total):
	contador[int(raw_input())]+= 1
for a,b in sorted(contador.most_common()):
	print "%d aparece %d vez(es)" % (a,b)
