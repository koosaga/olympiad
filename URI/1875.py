# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1875
# -*- coding: utf-8 -*-

TC = int(input())

for tc in range(TC):
	dicio = {"G" : 0,"R" : 0, "B" : 0}
	pontuacao = {"G" : {"R" : 1,"B" : 2}, "R" : {"G" : 2, "B" : 1}, "B" : {"G" : 1, "R" : 2}}
	N = int(input())
	for n in range(N):
		a,b = input().split()
		dicio[a] += pontuacao[a][b]
	if dicio["G"] == dicio["R"] and dicio["R"] == dicio["B"]:
		print("trempate")
	elif dicio["G"] > dicio["R"] and dicio["G"] > dicio["B"]:
		print("green")
	elif dicio["B"] > dicio["R"] and dicio["B"] > dicio["G"]:
		print("blue")
	elif dicio["R"] > dicio["G"] and dicio["R"] > dicio["B"]:
		print("red")
	else:
		print("empate")
