# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1457
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
tc = int(raw_input())
for teste in xrange(tc):
	entrada = raw_input()
	k = entrada.count("!")
	n = int(entrada.replace("!",""))
	resposta = 1
	while n > 0:
		resposta *= n
		n -= k
	print resposta
