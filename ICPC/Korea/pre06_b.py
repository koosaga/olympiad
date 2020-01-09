t = int(input())

for i in range(0, t):
	n = input()
	sq = str(int(n) * int(n))
	n = n[::-1]
	sq = sq[::-1]
	if sq[:len(n)] == n:
		print("YES")
	else:
		print("NO")
