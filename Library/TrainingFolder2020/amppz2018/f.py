t = int(input())

for i in range(0, t):
	a, b, c = tuple(map(int, input().split()))
	if c <= a + b:
		print("NIE")
	else:
		if 4 * a * b >= (c - a - b) * (c - a - b):
			print("NIE")
		else:
			print("TAK")
