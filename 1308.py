# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1308
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
tc = int(raw_input())
for tcdavez in xrange(tc):
	n = int(raw_input())
	if n == 0:
		print 0
		continue
	ini = 1
	fim = n
	resp = -1
	while ini <= fim:
		meio = (ini+fim)/2
		if ((meio)*(meio+1))/2 <= n:
			resp = meio
			ini = meio + 1
		else:
			fim = meio - 1
	print resp
