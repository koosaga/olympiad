# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1374
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
import datetime
while True:
	n = int(raw_input())
	if n == 0:
		break
	resp = 0
	cont = 0
	lista1 = []
	lista2 = []
	for i in xrange(n):
		a,b,c,d = [int(i) for i in raw_input().split()]
		lista1.append(datetime.datetime(c,b,a))
		lista2.append(d)
	for i in xrange(1,n):
		if lista1[i] - datetime.timedelta(days = 1) == lista1[i-1]:
			cont += 1
			resp += lista2[i] - lista2[i-1]
	print "%d %d" % (cont,resp)
