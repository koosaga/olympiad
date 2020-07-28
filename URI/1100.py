# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1100
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
from collections import deque
def bfs(graph,start,end):
	visited = set()
	queue = deque([(0,start)])
	while queue:
		distance,v = queue.popleft()
		if v == end:
			return distance
		if v not in visited:
			visited.add(v)
			for i in graph.get(v,[]):
				queue.append((distance+1,i))
	return -1
dicio = {"a":1,"b":2,"c":3,"d":4,"e":5,"f":6,"g":7,"h":8}
grafo = {}
for i in xrange(1,9):
	for j in xrange(1,9):
		complexo = complex(i,j)
		grafo[complexo] = [complexo+complex(1,2),complexo+complex(-1,2),complexo+complex(1,-2),complexo+complex(-1,-2),complexo+complex(2,1),complexo+complex(2,-1),complexo+complex(-2,1),complexo+complex(-2,-1)]
while True:
	try:
		a,b = raw_input().split()
	except EOFError:
		break
	coord1 = complex(dicio[a[0]], int(a[1]))
	coord2 = complex(dicio[b[0]], int(b[1]))
	print "To get from %s to %s takes %d knight moves." % (a,b,bfs(grafo,coord1,coord2))
