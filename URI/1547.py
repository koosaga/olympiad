# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1547
# encoding: utf-8
ordem = int(raw_input())
casos = []
alunos = []
for i in xrange(ordem):
	casos.append([int(i) for i in raw_input().split(" ")])
	alunos.append(raw_input())
for a,b in enumerate(casos):
	qt,s = b
	array = [abs(int(k)-s) for k in alunos[a].split(" ")]
	print 1 + array.index(min(array))
