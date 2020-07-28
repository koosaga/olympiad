# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1332
#!/usr/bin/env python2.7
# encoding : utf-8
ordem = int(raw_input())
for i in xrange(ordem):
	entrada = raw_input()
	if len(entrada)==3:
		if len([l for k,l in enumerate([j for j in entrada]) if "one"[k]==l])>=2:
			print 1
		elif len([l for k,l in enumerate([j for j in entrada]) if "two"[k]==l])>=2:
			print 2
	else:
		print 3
