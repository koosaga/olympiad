# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1134
#!/usr/bin/env python2.7
# encoding : utf-8
dicio = {1:0,2:0,3:0}
while True:
	entrada = int(raw_input())
	if entrada in [1,2,3]:
		dicio[entrada] += 1
	elif entrada == 4:
		print "MUITO OBRIGADO"
		print "Alcool: %d" % dicio[1]
		print "Gasolina: %d" % dicio[2]
		print "Diesel: %d" % dicio[3]
		break
