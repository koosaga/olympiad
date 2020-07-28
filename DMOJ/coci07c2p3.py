# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci07c2p3

R,C = [int(i) for i in input().split()]

matriz = [["#"]*(C+2)]
for i in range(R):
	entrada = input()
	linha = ["#"] + [j for j in entrada] + ["#"]
	matriz.append(linha)
matriz.extend([["#"]*(C+2)])

candidatos = []

for i in range(R+2):
	palavra = "".join(matriz[i])
	validos = [p for p in palavra.split("#") if len(p) >= 2]
	candidatos.extend(validos)

for i in range(C+2):
	palavra = ""
	for j in range(R+2):
		palavra += matriz[j][i]
	validos = [p for p in palavra.split("#") if len(p) >= 2]
	candidatos.extend(validos)

print(sorted(candidatos)[0])