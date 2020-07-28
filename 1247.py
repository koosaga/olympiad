# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1247
#!/usr/bin/env python2.7
# encoding : utf-8
while True:
	try:
		a,b,c = [int(i) for i in raw_input().split(" ")]
		tempo1 = 12.0/float(b)
		tempo2 = (((144)+(a**2))**0.5)/float(c)
		if tempo1 >= tempo2:
			print "S"
		else:
			print "N"
	except EOFError:
		break
