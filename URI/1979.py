# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1979
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
from collections import deque
while True:
	n = int(raw_input())
	if n == 0:
	 break
	grafo = {i: [] for i in xrange(n)}
	for i in xrange(n):
		grafo[i] = []
	processado = [0 for i in xrange(n)]
	cor = [-1 for i in xrange(n)]
	for linha in xrange(n):
		i = int(raw_input()) - 1
		for j in raw_input().split():
			grafo[i].append(int(j) - 1)
			grafo[int(j) -1].append(i)
	possivel = True
	for i in xrange(n):
		if processado[i]:
			continue
		if not possivel:
			break
		bfs = deque([])
		bfs.append(i)
		cor[i] = 0
		while bfs:
			v = bfs.popleft()
			if processado[v]:
				continue
			processado[v] = 1
			for j in grafo[v]:
				if cor[j] == cor[v]:
					possivel = False
					break
				cor[j] = 1 - cor[v]
				bfs.append(j)
	if possivel:
		print "SIM"
	else:
		print "NAO"
