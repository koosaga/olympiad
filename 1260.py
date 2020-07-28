# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1260
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
from collections import Counter
ordem = int(raw_input())
raw_input()
for caso_da_vez in xrange(ordem-1):
	contador = Counter()
	count = 0
	while True:
		entrada = raw_input()
		if entrada.split():
			contador[entrada] += 1.0
			count += 1.0
		else:
			break
	for a,b in sorted(contador.most_common()):
		print "%s %.4f" % (a,100.0*(b/count))
	print ""
contador = Counter()
count = 0
while True:
	try:
		entrada = raw_input()
		contador[entrada] += 1.0
		count += 1.0
	except EOFError:
		break
for a,b in sorted(contador.most_common()):
	print "%s %.4f" % (a,100.0*(b/count))
