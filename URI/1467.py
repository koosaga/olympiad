# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1467
#!/usr/bin/env python2.7
# encoding : utf-8
while True:
	try:
		e = raw_input()
		if e in ["0 0 0","1 1 1"]:
			print "*"
		elif e in ["1 0 0","0 1 1"]:
			print "A"
		elif e in ["1 0 1","0 1 0"]:
			print "B"
		else:
			print "C"
	except EOFError:
		break
