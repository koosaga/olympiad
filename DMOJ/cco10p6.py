# Ivan Carvalho
# Solution to https://dmoj.ca/problem/cco10p6
#!/usr/bin/env python2.7
# -*- coding : utf-8 -*-
alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_"
tamanho = 27
binario = [{}]
for i in alfabeto:
	binario[0][i] = i 
logartimos = range(32)
for i in alfabeto:
	davez = raw_input()
	binario.append({})
	binario[1][i] = davez
vez = int(raw_input())
raiz = min(int(vez**0.5)+1,vez)
for i in xrange(2,raiz+1):
	binario.append({})
	for j in alfabeto:
		binario[i][j] = binario[1][binario[i-1][j]]
resto = vez % raiz
quociente = vez - resto
quociente /= raiz
if resto != 0:
	resposta = binario[resto]
elif resto == 0 and vez != 0:
	resposta = binario[raiz]
for i in xrange(quociente):
	for j in alfabeto:
		resposta[j] = binario[raiz][resposta[j]]
entrada = [resposta[i] for i in raw_input()]
print "".join(entrada)