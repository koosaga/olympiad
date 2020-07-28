# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1430
#!/usr/bin/env python2.7
# -*- coding :  utf-8 -*-
dicio = {}
dicio["W"] = 1
dicio["H"] = 2 ** -1
dicio["Q"] = 2 ** -2
dicio["E"] = 2 ** -3
dicio["S"] = 2 ** -4
dicio["T"] = 2 ** -5
dicio["X"] = 2 ** -6
while True:
	entrada = raw_input()
	if entrada == "*":
		break
	resposta = 0
	lista = entrada.split("/")[1:]
	lista.pop()
	for i in lista:
		soma = 0
		for j in i:
			soma += dicio[j]
		resposta += (soma == 1)
	print resposta
