# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1258
#!/usr/bin/en vpython2.7
# -*- coding : utf-8 -*-
primeiro = True
while True:
	ordem = int(raw_input())
	if ordem == 0:
		break
	if not primeiro:
		print ""
	else:
		primeiro = False
	dicio = {"branco P":1,"branco M":2,"branco G":3,"vermelho P":4,"vermelho M":5,"vermelho G":6}
	inverso = {1:"branco P",2:"branco M",3:"branco G",4:"vermelho P",5:"vermelho M",6:"vermelho G"}
	array = []
	for davez in xrange(ordem):
		nome = raw_input()
		tamanho = dicio[raw_input()]
		array.append((tamanho,nome))
	for isso,aquilo in sorted(array):
		print "%s %s" % (inverso[isso],aquilo)
