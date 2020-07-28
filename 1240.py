# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1240
#!/usr/bin/env python2.7
# encoding : utf-8
ordem = int(raw_input())
for i in xrange(ordem):
	a,b = raw_input().split(" ")
	ta,tb = [len(a),len(b)]
	if tb > ta:
		print "nao encaixa"
	else:
		if b in a[::-1][:tb][::-1]:
			print "encaixa"
		else:
			print "nao encaixa"
