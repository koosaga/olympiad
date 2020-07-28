# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1540
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
casos = int(raw_input())
for caso in xrange(casos):
	a,b,c,d = [int(i) for i in raw_input().split()]
	exibir = "%.3lf" % ((d-b)/float(c-a))
	novoexbir = [i for i in exibir]
	novoexbir.pop()
	print "".join(novoexbir).replace(".",",")
