# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1241
#!/usr/bin/env python2.7
# encoding : utf-8
ordem = int(raw_input())
for i in xrange(ordem):
	a,b = raw_input().split(" ")
	a,b = a[::-1],b[::-1]
	if len(a)>=len(b):
		if all([a[j]==b[j] for j in xrange(len(b))]):
			print "encaixa"
		else:
			print "nao encaixa"
	else:
		print "nao encaixa"
