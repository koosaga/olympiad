# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci08c4p1
def exibe(lista):
	copia = [str(i) for i in lista]
	print(" ".join(copia))

lista = [int(i) for i in input().split()]

for vez in range(5):
	for i in range(len(lista) - 1):
		if lista[i] > lista[i+1]:
			lista[i],lista[i+1] = lista[i+1],lista[i]
			exibe(lista)
