# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1146
#!/usr/bin/env python2.7
# encoding : utf-8
while True:
	entrada = int(raw_input())
	if entrada == 0:
		break
	else:
		print " ".join([str(i) for i in xrange(1,entrada+1)])
