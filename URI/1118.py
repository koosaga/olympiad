# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1118
#!/usr/bin/env python2.7
# encoding : utf-8
array = []
while True:
	e = float(raw_input())
	if e >= 0 and e <= 10:
		array.append(e)
	else:
		print "nota invalida"
	if len(array)==2:
		print "media = %.2f" % (sum(array)/2.0)
		array = []
		while True:
			print "novo calculo (1-sim 2-nao)"
			receber = int(raw_input())
			if receber == 1:
				break
			elif receber == 2:
				break
		if receber == 2:
			break
