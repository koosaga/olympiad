# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1158
#!/usr/bin/env python2.7
# encoding : utf-8
ordem = int(raw_input())
for i in xrange(ordem):
	a,b = [int(i) for i in raw_input().split(" ") if i != ""]
	if a % 2 == 0:
		a += 1
	soma = 0
	count = 0
	while count < b:
		soma += a
		count += 1
		a += 2
	print soma
