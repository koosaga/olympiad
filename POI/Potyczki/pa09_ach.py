n = int(input())

if n % 4 <= 1:
	ans = 1
	for i in range(2, n, 4):
		ans *= i
	print(ans)

else:
	print(0)
