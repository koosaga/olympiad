# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1279
#!/usr/bin/env python2.7
# encoding : utf-8
array = []
while True:
	try:
		entrada = int(raw_input())
		huluculu = 0
		if entrada % 400 == 0:
			bissexto = 1
			array.append("This is leap year.")
		elif entrada % 100 == 0:
			bissexto = 0
		elif entrada % 4 == 0:
			bissexto = 1
			array.append("This is leap year.")
		else:
			bissexto = 0
		if entrada % 15 == 0 :
			array.append("This is huluculu festival year.")
			huluculu += 1
		if bissexto and entrada % 55 == 0:
			array.append("This is bulukulu festival year.")
		if bissexto == 0 and huluculu == 0:
			array.append("This is an ordinary year.")
		array.append("")
	except EOFError:
		break
array.pop(-1)
for i in array:
	print i
