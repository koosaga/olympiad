# Ivan Carvalho
# Solution to https://dmoj.ca/problem/gfssoc16s1
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
from collections import deque
mapa = {}
processado = {}
distancia = {}
a,b = [int(i) for i in raw_input().split()]
mapa["home"] = 0
mapa["Waterloo GO"] = a + 1;
for i in xrange(1,a+1):
	entrada = raw_input()
	mapa[entrada] = i
grafo = {}
for i in xrange(a+2):
	grafo[i] = []
	processado[i] = 0
	distancia[i] = float("inf")
for i in xrange(b):
	c,d = raw_input().split("-")
	grafo[mapa[c]].append(mapa[d])
	grafo[mapa[d]].append(mapa[c])
fila = deque()
fila.append(0)
distancia[0] = 0
processado[0] = 1
possivel = 0
while fila:
	v = fila[0]
	fila.popleft()
	if v == a + 1:
		print "%d" % (distancia[a+1])
		possivel = 1
		break
	for u in grafo[v]:
		if processado[u] == 1:
			continue
		processado[u] = 1
		distancia[u] = distancia[v] + 1
		fila.append(u)
if possivel == 0:
	print "RIP ACE"