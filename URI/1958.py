# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1958
#!/usr/bin/env python2.7
# encoding : utf-8
entrada = raw_input()
numero = float(entrada)
if entrada in ["0","+0","-0"]:
	print {"-0":"-0.0000E+00","0":"+0.0000E+00","+0":"+0.0000E+00"}[entrada]
else:
	texto = "%.4e" % (abs(numero))
	print "%s%s" % (["-","+"][numero>0],texto.upper())
