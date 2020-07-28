# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1256
# -*- coding: utf-8 -*-

def exibe(lista):
	conversao = [str(i) for i in lista]
	conversao.append("\\")
	print(" -> ".join(conversao)) 

TC = int(input())

for tc in range(TC):
	if tc != 0:
		print()
	A,B = [int(i) for i in input().split()]
	dicio = {}
	for i in range(A):
		dicio[i] = [i]
	entrada = [int(i) for i in input().split()]
	for i in entrada:
		dicio[i % A].append(i)
	for i in range(A):
		exibe(dicio[i])
