# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1816
#!/usr/bin/env/python2.7
# -*- coding : utf -*-
instancia = 1
while True:
	ordem = int(raw_input())
	if ordem == 0:
		break
	print "Instancia %d" % instancia
	instancia += 1
	resposta = []
	array = [i for i in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ']
	entrada = [int(i) for i in raw_input().split()]
	for i in entrada:
		resposta.append(array[i-1])
		antigo = array.pop(i-1)
		array.insert(0,antigo)
	print "".join(resposta)
	print ""
