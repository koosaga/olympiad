# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1800
#!/usr/bin/env python2.7
# encoding : utf-8
q,e = [int(i) for i in raw_input().split(" ")]
jaesteve = [int(k) for k in raw_input().split(" ")]
for l in xrange(q):
	agora = int(raw_input())
	if agora in jaesteve:
		print 0
	else:
		print 1
		jaesteve.append(agora)
