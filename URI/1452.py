# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1452
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
while True:
	n,m = [int(i) for i in raw_input().split()]
	if n == 0 and m == 0:
		break
	servidores = []
	usuarios = []
	conexoes = 0
	for i in xrange(n):
		servidores.append(set(raw_input().split()[1:]))
	for i in xrange(m):
		usuarios.append(set(raw_input().split()[1:]))
	for i in usuarios:
		for j in servidores:
			if j.intersection(i):
				conexoes += 1
	print conexoes
