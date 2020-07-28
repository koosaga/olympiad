# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1237
#!/usr/bin/env python2.7
# -*- coding : utf-8
while True:
	try:
		a = raw_input()
	except EOFError:
		break
	b = raw_input()
	minor,bigger = sorted([a,b],key=lambda x:len(x))
	index = 1
	answer = 0
	for i in xrange(len(a)):
		while index <= len(a) and a[i:index] in b:
			if index - i > answer:
				answer = index - i
			index += 1
		index = i+1
	print answer
