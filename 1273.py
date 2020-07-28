# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1273
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
verdade = False
while True:
	ordem = int(raw_input())
	if ordem == 0:
		break
	if verdade:
		print ""
	else:
		verdade = True
	array = []
	for i in xrange(ordem):
		array.append(raw_input())
	maximo = max([len(k) for k in array])
	for i in array:
		print "%s%s" % (" "*(maximo-len(i)),i)
