# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1076
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
from collections import defaultdict
def dfs(graph,start,total_vertices):
	count = 0
	alreadybeen = [1 for i in xrange(total_vertices)]
	stack = [start]
	while stack:
		v = stack.pop()
		if alreadybeen[v]:
			count += 1
			alreadybeen[v] = 0
			stack.extend(graph[v])
	return count
casos_no_total = int(raw_input())
for caso_da_vez in xrange(casos_no_total):
	vertice_inicial = int(raw_input())
	vertices_total,arestas_total = [int(i) for i in raw_input().split(" ")]
	grafo = defaultdict(list)
	for aresta_da_vez in xrange(arestas_total):
		aresta1, aresta2 = [int(i) for i in raw_input().split(" ")]
		grafo[aresta1].append(aresta2)
		grafo[aresta2].append(aresta1)
	print 2*dfs(grafo,vertice_inicial,vertices_total)-2
