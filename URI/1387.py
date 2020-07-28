# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1387
#!/usr/bin/env python2.7
# encoding : utf-8
while True:
	a,b = [int(i) for i in raw_input().split(" ")]
	if a== 0 and b == 0:
		break
	else:
		print a+b
