# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1259
#!/usr/bin/env python2.7
#encoding : utf-8
ordem = int(raw_input())
pares = []
impares = []
for i in xrange(ordem):
	j = int(raw_input())
	if j % 2 == 0:
		pares.append(j)
	else:
		impares.append(j)
for i in sorted(pares):
	print i
for i in sorted(impares)[::-1]:
	print i
