# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/2049
#!/usr/bin/env/python2.7
# -*- coding : utf-8 -*-
instancia = 1
while True:
	entrada = raw_input()
	if entrada == '0':
		break
	if instancia != 1:
		print ""
	checar = raw_input()
	print "Instancia %d" % instancia
	instancia += 1
	if entrada in checar:
		print "verdadeira"
	else:
		print "falsa"
