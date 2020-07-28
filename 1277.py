# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1277
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
casos = int(raw_input())
for caso_da_vez in xrange(casos):
	numero = int(raw_input())
	alunos = raw_input().split()
	presenca = [k.replace("M","") for k in raw_input().split()]
	faltas = []
	for aluno,falta in zip(alunos,presenca):
		if falta.count("P")/float(len(falta)) < 0.75 :
			faltas.append(aluno)
	print " ".join(faltas)
