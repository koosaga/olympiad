# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/2028
#!/usr/bin/env python2.7
# -*- coidng : utf-8 -*-
caso = 1
while True:
	try :
		ordem = int(raw_input())
	except EOFError:
		break
	vetor = ["0"]
	if ordem == 0:
		print "Caso %d: 1 numero\n0\n" % caso
		caso += 1
		continue
	for i in xrange(1,ordem+1):
		vetor.extend([str(i)]*i)
	print "Caso %d: %d numeros\n%s\n" % (caso,len(vetor)," ".join(vetor))
	caso += 1
