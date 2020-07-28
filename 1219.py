# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1219
#!/usr/bin/env python2.7
# encoding : utf-8
from math import pi as pi
def heron(x,y,z):
	p = (x+y+z)/2.0
	return ((p)*(p-x)*(p-y)*(p-z))**0.5
while True:
	try:
		a,b,c = sorted([float(i) for i in raw_input().split(" ")])
		area = heron(a,b,c)
		raiozinho = 2.0*area/(a+b+c)
		raiozao = (a*b*c)/(4.0*area)
		menor = pi * (raiozinho**2)
		print "%.4f %.4f %.4f" % (pi*(raiozao**2)-area,area-menor,menor)
	except EOFError:
		break
