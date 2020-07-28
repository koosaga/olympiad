# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci06c5p1
lista = [1,0,0]

entrada = input()

for i in entrada:
	if i == "A":
		lista[0],lista[1] = lista[1],lista[0]
	elif i == "B":
		lista[1],lista[2] = lista[2],lista[1]
	else:
		lista[0],lista[2] = lista[2],lista[0]

if lista[0] == 1:
	print(1)
elif lista[1] == 1:
	print(2)
else :
	print(3)
