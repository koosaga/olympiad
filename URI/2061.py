# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/2061
#!/usr/bin/env python2.7
# encoding : utf-8
a,b = [int(i) for i in raw_input().split(" ")]
abriu = 0
fechou = 0
for i in xrange(b):
	entrada = raw_input()
	if entrada ==  "fechou":
		fechou += 1
	else:
		abriu += 1
print a+ fechou - abriu
