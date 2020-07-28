# Ivan Carvalho
# Solution to https://dmoj.ca/problem/ccc10j5
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
a,b = [int(i) for i in raw_input().split()]
c,d = [int(i) for i in raw_input().split()]
print bfs(grafo,complex(a,b),complex(c,d))