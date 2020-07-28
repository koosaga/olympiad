# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/2057
#!/usr/bin/env python2.7
# encoding : utf-8
numero = sum([int(i) for i in raw_input().split(" ")])
if numero < 0:
	print numero + 24
elif numero < 24:
	print numero
else:
	print numero-24
