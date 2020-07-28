# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1212
#!/usr/bin/env python2.7
# encoding : utf-8
while True:
	a,b = sorted(raw_input().split(" "),key=lambda x: -len(x))
	multiply = len(a)-len(b)
	b = ("0"*multiply) +b
	if a == "0" and b=="0":
		break
	else :
		carry = 0
		arraya = [int(i) for i in a[::-1]] + [0]
		arrayb = [int(i) for i in b[::-1]] + [0]
		for i in xrange(len(a)):
			if arraya[i] + arrayb[i] >= 10:
				carry += 1
				arraya[i+1] += 1
		if carry== 0:
			print "No carry operation."
		elif carry == 1:
			print "1 carry operation."
		else:
			print "%d carry operations." % carry
