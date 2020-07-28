# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1198
#!/usr/bin/env python2.7
# encoding : utf-8
while True:
	try:
		a,b = [int(i) for i in raw_input().split(" ")]
		print abs(a-b)
	except EOFError:
		break
