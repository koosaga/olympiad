# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci14c5p4

N = [int(i) for i in input()]

primeiro = -1

for i in range(len(N)):
	if i == 0:
		continue
	if N[i] % 2 == N[i-1] % 2:
		primeiro = i
		break

if N[primeiro] == 0:
	N[primeiro] = 1
	for i in range(primeiro+1,len(N),2):
		N[i] = 0
		if i + 1 < len(N):
			N[i+1] = 1
	print("".join([str(i) for i in N]))
elif N[primeiro] == 9:
	N[primeiro] = 8
	for i in range(primeiro+1,len(N),2):
		N[i] = 9
		if i + 1 < len(N):
			N[i+1] = 8
	print("".join([str(i) for i in N]))
else:
	
	copia1 = [i for i in N]
	copia2 = [i for i in N]
	
	copia1[primeiro] -= 1
	if copia1[primeiro] % 2 == 0:
		vainolugar = [9,8]
	else:
		vainolugar = [8,9]
	for i in range(primeiro+1,len(N),2):
		copia1[i] = vainolugar[0]
		if i + 1 < len(N):
			copia1[i+1] = vainolugar[1]
	inteiro1 = int("".join([str(i) for i in copia1]))

	copia2[primeiro] += 1
	if copia1[primeiro] % 2 == 0:
		vainolugar = [1,0]
	else:
		vainolugar = [0,1]
	for i in range(primeiro+1,len(N),2):
		copia2[i] = vainolugar[0]
		if i + 1 < len(N):
			copia2[i+1] = vainolugar[1]

	inteiro2 = int("".join([str(i) for i in copia2]))

	original = int("".join([str(i) for i in N]))
	
	if inteiro2 - original == original - inteiro1:
		print("%d %d" % (inteiro1,inteiro2))
	elif inteiro2 - original < original - inteiro1:
		print(inteiro2)
	else:
		print(inteiro1)