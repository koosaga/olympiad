# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci14c2p1

def getgrupo(val,lista):
	for i,sublista in enumerate(lista):
		if val in sublista:
			return i
	return -1

grupos = [[],["a","b","c"],
	["d","e","f"], ["g","h","i"],
	["j","k","l"], ["m","n","o"],
	["p","q","r","s"],["t","u","v"],
	["w","x","y","z"]
]

resposta = []
permutacao = [int(i) for i in input().split()]
entrada = input()

for i in range(len(entrada)):

	if i >= 1 and getgrupo(entrada[i],grupos) == getgrupo(entrada[i-1],grupos):
		resposta.append("#")

	qual = getgrupo(entrada[i],grupos)
	qtd = grupos[qual].index(entrada[i]) + 1
	resposta.extend([str(permutacao.index(qual+1)+1)]*qtd)

print("".join(resposta))