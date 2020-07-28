# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1215
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
array = []
def funcao(x):
	if x.isalpha():
		return x
	else:
		return " "
while True:
	try:
		entrada = raw_input().lower()
		array.append("".join([funcao(k) for k in entrada]))
	except EOFError:
		break
aquilo = set(" ".join(array).split(" "))
aquilo.remove("")
for i in sorted(aquilo,key=lambda x: (ord(x[0]),x)):
	print i
