// Ivan Carvalho
// Solution to https://dmoj.ca/problem/thicc17p1
n,m = [int(i) for i in raw_input().split()]
modulo = 1000000007
entrada = [int(i) for i in raw_input().split()]
entrada.sort()
resp = 0
contador = 0
pot = 0
for i in entrada[::-1]:
	resp = (resp + pow(i,pot,modulo)) % modulo
	contador += 1
	if contador % m == 0:
		pot += 1
print resp