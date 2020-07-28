# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1278
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
exibir = False
while True:
	lines = int(raw_input())
	if lines == 0:
		break
	if exibir:
		print ""
	else:
		exibir = True
	array = []
	for i in xrange(lines):
		entrada = raw_input().split()
		array.append(" ".join(entrada))
	tamanho = max([len(i) for i in array])
	for i in array:
		print "%s%s" % (" "*(tamanho-len(i)),i)
