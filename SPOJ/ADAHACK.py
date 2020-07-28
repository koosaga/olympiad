# Ivan Carvalho
# Solution to https://www.spoj.com/problems/ADAHACK/
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
modulo = 10**11 + 3
def inv(a):
	return pow(a,modulo-2,modulo)
while True:
	try:
		entrada = raw_input()
	except EOFError:
		break
	array = [int(i) for i in entrada.split()]
	a = 1
	b = 0
	flag = 0
	for i in xrange(4):
		if flag == 1:
			break
		x1 = array[i]
		x2 = array[i+1]
		x3 = array[i+2]
		inv1 = inv(x1)
		if(x1 == 0 or inv1*x2 == 1):
			continue
		b = (x2*x2*inv1 - x3)*inv(inv1*x2 - 1)
		b %= modulo
		a = (x2 - b)*inv1
		a %= modulo
		flag = 1
	for i in xrange(4):
		if flag == 1:
			break
		x1 = array[i]
		x2 = array[i+1]
		x3 = array[i+2]
		inv2 = inv(x2)
		if(x2 == 0 or inv2*x1 == 1):
			continue
		b = (x3*x1*inv2 - x2)*inv(inv2*x1 - 1)
		b %= modulo
		a = (x3 - b)*inv2
		a %= modulo
		flag = 1
	x7 = (a*array[5] + b) % modulo
	print x7 