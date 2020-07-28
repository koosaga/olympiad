# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1427
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
casos = int(raw_input())
for caso_da_vez in xrange(casos):
	ordem = int(raw_input())
	pai = {}
	grafo = {}
	dicio = {}
	reverso = {}
	for indice,nome in enumerate(raw_input().split()) :
		dicio[indice] = nome
		reverso[nome] = indice
	for davez in xrange(ordem):
		grafo[davez] = {}
		pai[davez] = {}
		for alvo,peso in enumerate([int(i) for i in raw_input().split()]):
			if peso == -1 :
				grafo[davez][alvo] = float("inf")
				pai[davez][alvo] = -1
			else :
				grafo[davez][alvo] = peso
				pai[davez][alvo] =  alvo
	for k in xrange(ordem):
		for i in xrange(ordem):
			for j in xrange(ordem):
				distancia = grafo[i][k]+ grafo[k][j]
				if distancia < grafo[i][j]:
					grafo[i][j] = distancia
					pai[i][j] = pai[i][k]
	consultas = int(raw_input())
	for consulta_da_vez in xrange(consultas):
		empregado,partida,destino = raw_input().split()
		codigo1 = reverso[partida]
		codigo2 = reverso[destino]
		if pai[codigo1][codigo2] == -1:
			print "Sorry Mr %s you can not go from %s to %s" % (empregado,partida,destino)
		else:
			print "Mr %s to go from %s to %s, you will receive %d euros" % (empregado,partida,destino,grafo[codigo1][codigo2])
			caminho = [codigo1]
			if codigo1 == codigo2:
				caminho.append(codigo2)
			while codigo1 != codigo2:
				codigo1 = pai[codigo1][codigo2]
				caminho.append(codigo1)
			print "Path:%s" % " ".join([dicio[k] for k in caminho])
