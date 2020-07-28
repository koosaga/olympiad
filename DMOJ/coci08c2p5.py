# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci08c2p5
# -*- coding : utf-8 -*-

entrada = input()

somatorio = 1
nos = 1

for caractere in entrada:
	if caractere == "P":
		continue
	elif caractere == "L":
		somatorio = somatorio * 2
	elif caractere == "R":
		somatorio = somatorio*2 + nos
	else:
		somatorio = somatorio*5 + nos
		nos *= 3

print(somatorio)