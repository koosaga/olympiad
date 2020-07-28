# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1087
#!/usr/bin/env python2.7
# encoding : utf-8
while True:
	a,b,c,d = [int(i) for i in raw_input().split(" ")]
	diferencax = abs(a-c)
	diferencay = abs(b-d)
	if a == 0 and b == 0 and c== 0 and d == 0:
		break
	else:
		if a == c and b == d:
			print 0
		elif a==c or b == d:
			print 1
		elif diferencax == diferencay :
			print 1
		else:
			print 2
