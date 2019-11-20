n, k = map(int, input().split())
pwr = 1
cnt = 0

line = ""
while pwr < n:
	val = 0

	for j in range(0, n):
		if (j & pwr) == 0:
			val += (2 ** j)
	
	line = line + "\n" + ("A=(((A>>" + str(pwr) + ")&" + str(val) + ")+(A&" + str(val) + "))")
	cnt += 1
	pwr *= 2

print(str(cnt) + line)
